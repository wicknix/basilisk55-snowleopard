/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "WMF.h"
#include "WMFDecoderModule.h"
#include "WMFVideoMFTManager.h"
#include "WMFAudioMFTManager.h"
#include "MFTDecoder.h"
#include "mozilla/DebugOnly.h"
#include "mozilla/Services.h"
#include "WMFMediaDataDecoder.h"
#include "nsAutoPtr.h"
#include "nsIWindowsRegKey.h"
#include "nsComponentManagerUtils.h"
#include "nsServiceManagerUtils.h"
#include "nsIGfxInfo.h"
#include "nsWindowsHelpers.h"
#include "GfxDriverInfo.h"
#include "mozilla/gfx/gfxVars.h"
#include "MediaInfo.h"
#include "MediaPrefs.h"
#include "prsystem.h"
#include "mozilla/Maybe.h"
#include "mozilla/StaticMutex.h"
#include "mozilla/WindowsVersion.h"
#include "MP4Decoder.h"
#include "VPXDecoder.h"

namespace mozilla {

static Atomic<bool> sDXVAEnabled(false);

WMFDecoderModule::WMFDecoderModule()
  : mWMFInitialized(false)
{
}

WMFDecoderModule::~WMFDecoderModule()
{
  if (mWMFInitialized) {
    DebugOnly<HRESULT> hr = wmf::MFShutdown();
    NS_ASSERTION(SUCCEEDED(hr), "MFShutdown failed");
  }
}

/* static */
void
WMFDecoderModule::Init()
{
  sDXVAEnabled = gfx::gfxVars::CanUseHardwareVideoDecoding();
}

/* static */
int
WMFDecoderModule::GetNumDecoderThreads()
{
  int32_t numCores = PR_GetNumberOfProcessors();

  // If we have more than 4 cores, let the decoder decide how many threads.
  // On an 8 core machine, WMF chooses 4 decoder threads
  const int WMF_DECODER_DEFAULT = -1;
  int32_t prefThreadCount = WMF_DECODER_DEFAULT;
  if (XRE_GetProcessType() != GeckoProcessType_GPU) {
    prefThreadCount = MediaPrefs::PDMWMFThreadCount();
  }
  if (prefThreadCount != WMF_DECODER_DEFAULT) {
    return std::max(prefThreadCount, 1);
  } else if (numCores > 4) {
    return WMF_DECODER_DEFAULT;
  }
  return std::max(numCores - 1, 1);
}

nsresult
WMFDecoderModule::Startup()
{
  mWMFInitialized = SUCCEEDED(wmf::MFStartup());
  return mWMFInitialized ? NS_OK : NS_ERROR_FAILURE;
}

already_AddRefed<MediaDataDecoder>
WMFDecoderModule::CreateVideoDecoder(const CreateDecoderParams& aParams)
{
  // Temporary - forces use of VPXDecoder when alpha is present.
  // Bug 1263836 will handle alpha scenario once implemented. It will shift
  // the check for alpha to PDMFactory but not itself remove the need for a
  // check.
  if (aParams.VideoConfig().HasAlpha()) {
    return nullptr;
  }

  nsAutoPtr<WMFVideoMFTManager> manager(
    new WMFVideoMFTManager(aParams.VideoConfig(),
                           aParams.mKnowsCompositor,
                           aParams.mImageContainer,
                           sDXVAEnabled));

  if (!manager->Init()) {
    return nullptr;
  }

  RefPtr<MediaDataDecoder> decoder =
    new WMFMediaDataDecoder(manager.forget(), aParams.mTaskQueue, aParams.mCallback);

  return decoder.forget();
}

already_AddRefed<MediaDataDecoder>
WMFDecoderModule::CreateAudioDecoder(const CreateDecoderParams& aParams)
{
  nsAutoPtr<WMFAudioMFTManager> manager(new WMFAudioMFTManager(aParams.AudioConfig()));

  if (!manager->Init()) {
    return nullptr;
  }

  RefPtr<MediaDataDecoder> decoder =
    new WMFMediaDataDecoder(manager.forget(), aParams.mTaskQueue, aParams.mCallback);
  return decoder.forget();
}

static bool
CanCreateMFTDecoder(const GUID& aGuid)
{
  if (FAILED(wmf::MFStartup())) {
    return false;
  }
  bool hasdecoder = false;
  {
    RefPtr<MFTDecoder> decoder(new MFTDecoder());
    hasdecoder = SUCCEEDED(decoder->Create(aGuid));
  }
  wmf::MFShutdown();
  return hasdecoder;
}

template<const GUID& aGuid>
static bool
CanCreateWMFDecoder()
{
  static StaticMutex sMutex;
  StaticMutexAutoLock lock(sMutex);
  static Maybe<bool> result;
  if (result.isNothing()) {
    result.emplace(CanCreateMFTDecoder(aGuid));
  }
  return result.value();
}

static bool
IsH264DecoderBlacklisted()
{
#ifdef BLACKLIST_CRASHY_H264_DECODERS
  WCHAR systemPath[MAX_PATH + 1];
  if (!ConstructSystem32Path(L"msmpeg2vdec.dll", systemPath, MAX_PATH + 1)) {
    // Cannot build path -> Assume it's not the blacklisted DLL.
    return false;
  }

  DWORD zero;
  DWORD infoSize = GetFileVersionInfoSizeW(systemPath, &zero);
  if (infoSize == 0) {
    // Can't get file info -> Assume we don't have the blacklisted DLL.
    return false;
  }
  auto infoData = MakeUnique<unsigned char[]>(infoSize);
  VS_FIXEDFILEINFO *vInfo;
  UINT vInfoLen;
  if (GetFileVersionInfoW(systemPath, 0, infoSize, infoData.get()) &&
    VerQueryValueW(infoData.get(), L"\\", (LPVOID*)&vInfo, &vInfoLen))
  {
    if ((vInfo->dwFileVersionMS == ((12u << 16) | 0u))
        && ((vInfo->dwFileVersionLS == ((9200u << 16) | 16426u))
            || (vInfo->dwFileVersionLS == ((9200u << 16) | 17037u)))) {
      // 12.0.9200.16426 & .17037 are blacklisted on Win64, see bug 1242343.
      return true;
    }
  }
#endif // BLACKLIST_CRASHY_H264_DECODERS
  return false;
}

/* static */ bool
WMFDecoderModule::HasH264()
{
  if (IsH264DecoderBlacklisted()) {
    return false;
  }
  return CanCreateWMFDecoder<CLSID_CMSH264DecoderMFT>();
}

/* static */ bool
WMFDecoderModule::HasAAC()
{
  return CanCreateWMFDecoder<CLSID_CMSAACDecMFT>();
}

bool
WMFDecoderModule::SupportsMimeType(const nsACString& aMimeType,
                                   DecoderDoctorDiagnostics* aDiagnostics) const
{
  UniquePtr<TrackInfo> trackInfo = CreateTrackInfoWithMIMEType(aMimeType);
  if (!trackInfo) {
    return false;
  }
  return Supports(*trackInfo, aDiagnostics);
}

bool
WMFDecoderModule::Supports(const TrackInfo& aTrackInfo,
                           DecoderDoctorDiagnostics* aDiagnostics) const
{
  // Check bit depth of video.
  // XXXMC: This is here in case we want to start accepting HDR video. Do we?
  //        This currently defaults to a fail if video bitdepth != 8
  const auto videoInfo = aTrackInfo.GetAsVideoInfo();
  if (videoInfo && !SupportsBitDepth(videoInfo->mBitDepth, aDiagnostics)) {
    return false;
  }

  if ((aTrackInfo.mMimeType.EqualsLiteral("audio/mp4a-latm") ||
       aTrackInfo.mMimeType.EqualsLiteral("audio/mp4")) &&
       WMFDecoderModule::HasAAC()) {
    return true;
  }
  if (MP4Decoder::IsH264(aTrackInfo.mMimeType) && WMFDecoderModule::HasH264()) {
    if (!MediaPrefs::PDMWMFAllowUnsupportedResolutions()) {
      const VideoInfo* videoInfo = aTrackInfo.GetAsVideoInfo();
      MOZ_ASSERT(videoInfo);
      // Check Windows format constraints, based on:
      // https://msdn.microsoft.com/en-us/library/windows/desktop/dd797815(v=vs.85).aspx
      if (IsWin8OrLater()) {
        // Windows >7 supports at most 4096x2304.
        if (videoInfo->mImage.width > 4096 || videoInfo->mImage.height > 2304) {
          return false;
        }
      } else {
      // Windows 7 supports at most 1920x1088.
        if (videoInfo->mImage.width > 1920 || videoInfo->mImage.height > 1088) {
          return false;
        }
      }
    }
    return true;
  }
  if (aTrackInfo.mMimeType.EqualsLiteral("audio/mpeg") &&
      CanCreateWMFDecoder<CLSID_CMP3DecMediaObject>()) {
    return true;
  }
  if (MediaPrefs::PDMWMFVP9DecoderEnabled() && sDXVAEnabled) {
    if ((VPXDecoder::IsVP8(aTrackInfo.mMimeType) ||
         VPXDecoder::IsVP9(aTrackInfo.mMimeType)) &&
        CanCreateWMFDecoder<CLSID_WebmMfVpxDec>()) {
      return true;
    }
  }

  // Some unsupported codec.
  return false;
}

PlatformDecoderModule::ConversionRequired
WMFDecoderModule::DecoderNeedsConversion(const TrackInfo& aConfig) const
{
  if (aConfig.IsVideo() && MP4Decoder::IsH264(aConfig.mMimeType)) {
    return ConversionRequired::kNeedAnnexB;
  } else {
    return ConversionRequired::kNeedNone;
  }
}

} // namespace mozilla
