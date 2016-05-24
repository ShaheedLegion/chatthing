project("core")

# Dependencies
# ------------------------------------------------------------------------------

# GTK
if(SFML_PLATFORM STREQUAL "linux")
  message(STATUS "Looking for GTK2.")
  find_package(GTK2 REQUIRED gtk)
  if(GTK2_FOUND)
    include_directories(${GTK2_INCLUDE_DIRS})
    message("TESTING")
  else()
    message(FATAL_ERROR "GTK not found!")
  endif()
endif()

# On mac we must compile with -fno-pic
if(APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-pic")
endif()

if(SFML_PLATFORM STREQUAL "android")
  list(APPEND pi_SOURCES
    "${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c"
  )
  include_directories("${ANDROID_NDK}/sources/android/native_app_glue")
endif() 

# Sources.cmake
# ------------------------------------------------------------------------------

set(ANDROID_EXCLUDE "-exclude=android")
if(SFML_PLATFORM STREQUAL "android")
  set(ANDROID_EXCLUDE "")
endif()

message(STATUS "Gathering source files for core")
find_package(PythonInterp)
execute_process(
  COMMAND
    "${PYTHON_EXECUTABLE}"
    "${CMAKE_SOURCE_DIR}/bin/gen_cmake_files.py"
    "${core_SOURCE_DIR}"
    "-root=${core_SOURCE_DIR}"
    ${ANDROID_EXCLUDE}
  WORKING_DIRECTORY
    "${CMAKE_SOURCE_DIR}"
  OUTPUT_FILE
    "${core_BINARY_DIR}/Sources.cmake"
)

message(STATUS "Adding - ${core_BINARY_DIR}/Sources.cmake")
include("${core_BINARY_DIR}/Sources.cmake")

# Library: base
# ------------------------------------------------------------------------------

add_library("core" STATIC ${core_SOURCES})
set_property(TARGET "core" PROPERTY FOLDER "Libraries")

