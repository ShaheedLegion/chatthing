
# OpenSSL ----------------------------------------------------------------------

add_custom_target(copy_openssl)

if(SFML_PLATFORM STREQUAL "android")
  # On android the linking to the prebuilt libraries is done in the Android.mk file.

  set(_OPENSSL_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/ext/android/openssl-1.0.1g/lib/${ANDROID_ABI}")
  set("OPENSSL_LIBRARIES"
    "${_OPENSSL_LIBRARY_PATH}/libssl.a"
    "${_OPENSSL_LIBRARY_PATH}/libcrypto.a"
  )
  set("OPENSSL_INCLUDE_DIR" "${CMAKE_SOURCE_DIR}/ext/android/openssl-1.0.1g/include")

  # Copy the files over to the output location.
  set(_SOURCE_DIR "${CMAKE_SOURCE_DIR}/ext/android/openssl-1.0.1g/lib/${ANDROID_ABI}")
  set(_DEST_DIR "${CMAKE_BINARY_DIR}/out/android/${ANDROID_ABI}")

  # Copy the freetype library.
  add_custom_command(
    TARGET copy_openssl
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${_SOURCE_DIR}/libcrypto.a" "${_DEST_DIR}/libcrypto.a"
  )

  # Copy the freetype library.
  add_custom_command(
    TARGET copy_openssl
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${_SOURCE_DIR}/libssl.a" "${_DEST_DIR}/libssl.a"
  )

elseif(UNIX)
  find_package(OpenSSL)
  if(NOT OPENSSL_FOUND)
    message(FATAL_ERROR "OpenSSL not found. Please specify root directory via OPENSSL_ROOT_DIR")
  endif(NOT OPENSSL_FOUND)
else()
  if(NOT OPENSSL_ROOT)
    message(STATUS "OPENSSL_ROOT: ${OPENSSL_ROOT}")
    set(OPENSSL_ROOT "${CMAKE_SOURCE_DIR}/third_party/ssl/openssl-1.0.1c-msvc" CACHE PATH "Root of OpenSSL install")
  endif()
  if(MSVC)
    set(OPENSSL_LIBRARIES
      "${OPENSSL_ROOT}/lib/libeay32.lib"
      "${OPENSSL_ROOT}/lib/ssleay32.lib"
      "ws2_32"
    )
    set(OPENSSL_INCLUDE_DIR "${OPENSSL_ROOT}/include")
  else(MSVC)
    set(OPENSSL_LIBRARIES "${CMAKE_SOURCE_DIR}/third_party/ssl/openssl-0.9.8l-cygwin-mingw/libssl.a")
    set(OPENSSL_LIBRARIES ${OPENSSL_LIBRARIES} "${CMAKE_SOURCE_DIR}/third_party/ssl/openssl-0.9.8l-cygwin-mingw/libcrypto.a")
    set(OPENSSL_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/third_party/ssl/include")
  endif(MSVC)
endif()
