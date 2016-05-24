
# Set the windows version.
if(SFML_PLATFORM STREQUAL "win32")

  add_definitions("-DNOMINMAX")
  add_definitions("-D_UNICODE" "-DUNICODE")

  if(MINGW)
    # Windows XP and up
    add_definitions("-D_WIN32_WINNT=0x0501")
    message(STATUS "WIN32: Setting windows version to XP")
  else()
    # Windows 7 and up
    add_definitions("-D_WIN32_WINNT=0x0601")
    message(STATUS "WIN32: Setting windows version to Vista")
  endif()

  # Set up MSVC.
  include("cmake/msvc.cmake")

endif(SFML_PLATFORM STREQUAL "win32")
