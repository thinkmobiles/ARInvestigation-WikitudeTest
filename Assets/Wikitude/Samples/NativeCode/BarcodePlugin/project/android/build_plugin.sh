#!/bin/sh
echo ""
echo "Compiling barcode.c..."
/Users/alexandruflorea/Library/Android/ndk/android-ndk-r10e/ndk-build NDK_PROJECT_PATH=/Users/alexandruflorea/Documents/Wikitude/SDK/Native/unity-wikitude-plugin/projects/android/BarcodePlugin NDK_APPLICATION_MK=Application.mk $*
# mv libs/armeabi/libbarcode.so /Users/alexandruflorea/Documents/Wikitude/SDK/Native/unity-wikitude-plugin/projects/unity/WikitudeUnityExample/Assets/Plugins/Android

echo ""
echo "Cleaning up / removing build folders..."  #optional..
rm -rf libs
rm -rf obj

echo ""
echo "Done!"
