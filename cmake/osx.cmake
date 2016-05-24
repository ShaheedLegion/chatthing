
if(SFML_PLATFORM STREQUAL "osx")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++1y -stdlib=libc++")

  set(CMAKE_SKIP_BUILD_RPATH false)
  set(CMAKE_BUILD_WITH_INSTALL_RPATH true)
  set(CMAKE_INSTALL_RPATH "@loader_path" "@loader_path/.." "@loader_path/../Frameworks")
  set(CMAKE_INSTALL_RPATH_USE_LINK_PATH true)

endif()
