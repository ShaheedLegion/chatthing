cmake_minimum_required(VERSION 2.6)

# Public Settings
# ------------------------------------------------------------------------------

# The name of the app to build.  (More human friendly)
set (SFML_APP_NAME "SpaceThing" CACHE STRING "Human friendly name of the app.")

project("${SFML_APP_NAME}")

# Try to set the SFML_PLATFORM automagically.
set(_SFML_DETECTED_PLATFORM "")
if(ANDROID)
  message(STATUS "Setting platform to: android")
  set(_SFML_DETECTED_PLATFORM "android")
elseif(WIN32)
  message(STATUS "Setting platform to: win32")
  set(_SFML_DETECTED_PLATFORM "win32")
elseif(APPLE)
  message(STATUS "Setting platform to: osx")
  set(_SFML_DETECTED_PLATFORM "osx")
elseif(UNIX)
  message(STATUS "Setting platform to: linux")
  set(_SFML_DETECTED_PLATFORM "linux")
endif()

if(NOT _SFML_DETECTED_PLATFORM)
  message(FATAL "Could not determine build platform.")
endif()

# win32 linux osx ios android
set(SFML_PLATFORM ${_SFML_DETECTED_PLATFORM} CACHE STRING
  "Set the target platform to build for. (win32, linux, osx, ios, android)")

# Project settings
# ------------------------------------------------------------------------------

if(NOT SFML_PLATFORM)
  message(FATAL_ERROR "SFML_PLATFORM *MUST* be specified. (win32, linux, osx, ios, android)")
endif()

# Output Location
# ------------------------------------------------------------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/out/${SFML_PLATFORM}")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Compile with C++11 enabled.
#if(NOT MSVC)
#  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
#endif()


include("cmake/${SFML_PLATFORM}.cmake")

include("cmake/sfml.cmake")

#include("cmake/intel_tools.cmake")

# Libraries
# ------------------------------------------------------------------------------

# pugixml
#add_subdirectory("third_party/pugixml-1.4")
#include_directories("${pugixml_SOURCE_DIR}/src")

# zlib
#add_subdirectory("third_party/zlib-1.2.8")
#set_property(TARGET "zlibstatic" PROPERTY FOLDER "third_party")
#set_property(TARGET "zlib" PROPERTY FOLDER "Ignore")
#set_property(TARGET "example" PROPERTY FOLDER "Ignore")
#set_property(TARGET "minigzip" PROPERTY FOLDER "Ignore")
#include_directories("${zlib_SOURCE_DIR}")
#include_directories("${zlib_BINARY_DIR}")

# openssl
#include("cmake/openssl.cmake")
#include_directories(${OPENSSL_INCLUDE_DIR})

# openal-soft (Only used on Android)
#if(SFML_PLATFORM STREQUAL "android")
#  set(LIBTYPE "STATIC")
#  add_subdirectory("third_party/openal-soft-1.16.0" "openal")
#endif()

# Libraries

include_directories("src")
add_subdirectory("src/core")
add_subdirectory("src/app")

