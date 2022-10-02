
# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Import the ARCore (Google Play Services for AR) library.
add_library(arcore SHARED IMPORTED)
set_target_properties(arcore PROPERTIES IMPORTED_LOCATION
                      ${ARCORE_LIBPATH}/${ANDROID_ABI}/libarcore_sdk_c.so
                      INTERFACE_INCLUDE_DIRECTORIES ${ARCORE_INCLUDE}
)

# Import the glm header file from the NDK.
add_library( glm INTERFACE )
set_target_properties( glm PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${GLM_INCLUDE})

# This is the main app library.
add_library(arcoreapp_native SHARED
           src/main/cpp/background_renderer.cc
        src/main/cpp/arcoreapp.cc
           src/main/cpp/jni_interface.cc
        src/main/cpp/texture.cc
           src/main/cpp/util.cc)

target_include_directories(arcoreapp_native PRIVATE
           src/main/cpp)
target_link_libraries(arcoreapp_native
                      android
                      log
                      GLESv2
                      glm
                      arcore)
