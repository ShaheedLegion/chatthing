set(SFML_SFML_ROOT_DIR "" CACHE PATH "SFML source root directory")
if(NOT SFML_SFML_ROOT_DIR)
  message(FATAL_ERROR "SFML not found. Please set SFML_SFML_ROOT_DIR.")
endif()

# On Android, we just use the headers.
add_subdirectory("${SFML_SFML_ROOT_DIR}" "sfml")

include_directories("${SFML_SFML_ROOT_DIR}/include")
include_directories("${SFML_SFML_ROOT_DIR}/src")

if(SFML_PLATFORM STREQUAL "android")
  # Set the output directories.
  set("LIBRARY_OUTPUT_PATH" "${CMAKE_BINARY_DIR}/out/android/${ANDROID_ABI}")
  set("EXECUTABLE_OUTPUT_PATH" "${CMAKE_BINARY_DIR}/out/android/${ANDROID_ABI}")

  # Reset the output location of sfml targets.
  set_target_properties(
    "sfml-network"
    "sfml-audio"
    "sfml-graphics"
    "sfml-window"
    "sfml-system"
    "sfml-main"
    PROPERTIES
      ARCHIVE_OUTPUT_DIRECTORY
        "${CMAKE_BINARY_DIR}/out/android/${ANDROID_ABI}"
      LIBRARY_OUTPUT_DIRECTORY
        "${CMAKE_BINARY_DIR}/out/android/${ANDROID_ABI}"
      EXECUTABLE_OUTPUT_DIRECTORY
        "${CMAKE_BINARY_DIR}/out/android/${ANDROID_ABI}"
  )

  # On Android we have to build openAL with SFML.
  add_dependencies("sfml-audio" "openal")

  # The locations where we want to copy files from/to.
  set(_SOURCE_DIR "${SFML_SFML_ROOT_DIR}/extlibs/libs-android/${ANDROID_ABI}")
  set(_DEST_DIR "${CMAKE_BINARY_DIR}/out/android/${ANDROID_ABI}")

  add_custom_target(copy_libraries)

  # Copy the freetype library.
  add_custom_command(
    TARGET copy_libraries
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${_SOURCE_DIR}/libfreetype.a" "${_DEST_DIR}/libfreetype.a"
  )

  # Copy the freetype library.
  add_custom_command(
    TARGET copy_libraries
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${_SOURCE_DIR}/libjpeg.a" "${_DEST_DIR}/libjpeg.a"
  )

  # Copy the FLAC library.
  add_custom_command(
    TARGET copy_libraries
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${_SOURCE_DIR}/libFLAC.a" "${_DEST_DIR}/libFLAC.a"
  )

  # Copy the FLAC++ library.
  add_custom_command(
    TARGET copy_libraries
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${_SOURCE_DIR}/libFLAC++.a" "${_DEST_DIR}/libFLAC++.a"
  )

  # Copy the vorbis library.
  add_custom_command(
    TARGET copy_libraries
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${_SOURCE_DIR}/libvorbis.a" "${_DEST_DIR}/libvorbis.a"
  )

  # Copy the vorbisenc library.
  add_custom_command(
    TARGET copy_libraries
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${_SOURCE_DIR}/libvorbisenc.a" "${_DEST_DIR}/libvorbisenc.a"
  )

  # Copy the vorbisfile library.
  add_custom_command(
    TARGET copy_libraries
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${_SOURCE_DIR}/libvorbisfile.a" "${_DEST_DIR}/libvorbisfile.a"
  )

  # Copy the ogg library.
  add_custom_command(
    TARGET copy_libraries
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${_SOURCE_DIR}/libogg.a" "${_DEST_DIR}/libogg.a"
  )

  add_dependencies("sfml-main" "copy_libraries")

endif()
