#!/bin/bash

# Check if correct number of arguments provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 [Build folder] [Folder containing .dylib files]"
    exit 1
fi

build_folder="$1"
nightly_app="${build_folder}/dist/basilisk/InterWeb.app"
dylib_folder="$2"

# 1. Copy dylibs from the specified folder
cp "${dylib_folder}/libc++.1.dylib" "${nightly_app}/Contents/MacOS/libc++.1.dylib"
cp "${dylib_folder}/libc++abi.dylib" "${nightly_app}/Contents/MacOS/libc++abi.dylib"
cp "${dylib_folder}/libMacportsLegacySystem.B.dylib" "${nightly_app}/Contents/MacOS/libMacportsLegacySystem.B.dylib"
cp "${dylib_folder}/libz.1.3.1.dylib" "${nightly_app}/Contents/MacOS/libz.1.3.1.dylib"

# 2. Link MacPorts Legacy-Support
install_name_tool -change /usr/lib/libSystem.B.dylib @executable_path/libMacportsLegacySystem.B.dylib "${nightly_app}/Contents/MacOS/XUL"
install_name_tool -change /usr/lib/libSystem.B.dylib @executable_path/libMacportsLegacySystem.B.dylib "${nightly_app}/Contents/MacOS/libmozglue.dylib"

# 3. Link Zlib
install_name_tool -change /usr/lib/libz.1.dylib @executable_path/libz.1.3.1.dylib "${nightly_app}/Contents/MacOS/XUL"

# 4. Link LibC++
install_name_tool -change /usr/lib/libc++.1.dylib @executable_path/libc++.1.dylib "${nightly_app}/Contents/MacOS/basilisk"
install_name_tool -change /usr/lib/libc++.1.dylib @executable_path/libc++.1.dylib "${nightly_app}/Contents/MacOS/XUL"
install_name_tool -change /usr/lib/libc++.1.dylib @executable_path/libc++.1.dylib "${nightly_app}/Contents/MacOS/libmozglue.dylib"
install_name_tool -change /usr/lib/libc++.1.dylib @executable_path/libc++.1.dylib "${nightly_app}/Contents/MacOS/libnss3.dylib"
install_name_tool -change /usr/lib/libc++.1.dylib @executable_path/libc++.1.dylib "${nightly_app}/Contents/MacOS/libfreebl3.dylib"
install_name_tool -change /usr/lib/libc++.1.dylib @executable_path/libc++.1.dylib "${nightly_app}/Contents/MacOS/libhunspell.dylib"
install_name_tool -change /usr/lib/libc++.1.dylib @executable_path/libc++.1.dylib "${nightly_app}/Contents/MacOS/liblgpllibs.dylib"
install_name_tool -change /usr/lib/libc++.1.dylib @executable_path/libc++.1.dylib "${nightly_app}/Contents/MacOS/libmozavcodec.dylib"
install_name_tool -change /usr/lib/libc++.1.dylib @executable_path/libc++.1.dylib "${nightly_app}/Contents/MacOS/libmozavutil.dylib"
install_name_tool -change /usr/lib/libc++.1.dylib @executable_path/libc++.1.dylib "${nightly_app}/Contents/MacOS/libnssckbi.dylib"
install_name_tool -change /usr/lib/libc++.1.dylib @executable_path/libc++.1.dylib "${nightly_app}/Contents/MacOS/libnssdbm3.dylib"
install_name_tool -change /usr/lib/libc++.1.dylib @executable_path/libc++.1.dylib "${nightly_app}/Contents/MacOS/libplugin_child_interpose.dylib"
install_name_tool -change /usr/lib/libc++.1.dylib @executable_path/libc++.1.dylib "${nightly_app}/Contents/MacOS/libsoftokn3.dylib"
install_name_tool -change /usr/lib/libc++.1.dylib @executable_path/libc++.1.dylib "${nightly_app}/Contents/MacOS/plugin-container.app/Contents/MacOS/plugin-container"
install_name_tool -change /usr/lib/libc++.1.dylib @executable_path/libc++.1.dylib "${nightly_app}/Contents/Resources/basilisk-bin"
