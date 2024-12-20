/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "PerformanceWorker.h"
#include "WorkerPrivate.h"

namespace mozilla {
namespace dom {

using namespace workers;

PerformanceWorker::PerformanceWorker(WorkerPrivate* aWorkerPrivate)
  : mWorkerPrivate(aWorkerPrivate)
{
  mWorkerPrivate->AssertIsOnWorkerThread();
}

PerformanceWorker::~PerformanceWorker()
{
  if (mWorkerPrivate) {
    mWorkerPrivate->AssertIsOnWorkerThread();
  }
}

void
PerformanceWorker::InsertUserEntry(PerformanceEntry* aEntry)
{
  if (mWorkerPrivate->PerformanceLoggingEnabled()) {
    nsAutoCString uri;
    nsCOMPtr<nsIURI> scriptURI = mWorkerPrivate->GetResolvedScriptURI();
    if (!scriptURI || NS_FAILED(scriptURI->GetHost(uri))) {
      // If we have no URI, just put in "none".
      uri.AssignLiteral("none");
    }
    Performance::LogEntry(aEntry, uri);
  }
  Performance::InsertUserEntry(aEntry);
}

TimeStamp
PerformanceWorker::CreationTimeStamp() const
{
  if (mWorkerPrivate) {
    return mWorkerPrivate->CreationTimeStamp();
  }
  return TimeStamp();
}

DOMHighResTimeStamp
PerformanceWorker::CreationTime() const
{
  if (mWorkerPrivate) {
    return mWorkerPrivate->CreationTime();
  }
  return DOMHighResTimeStamp();
}

} // dom namespace
} // mozilla namespace
