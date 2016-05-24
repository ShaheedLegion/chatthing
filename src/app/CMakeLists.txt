project("app")
cmake_minimum_required(VERSION 2.6)

# General project settings
# ------------------------------------------------------------------------------

find_package(PythonInterp)
execute_process(
  COMMAND
    "${PYTHON_EXECUTABLE}"
    "${CMAKE_SOURCE_DIR}/bin/gen_cmake_files.py"
    "${app_SOURCE_DIR}"
    "-root=${app_SOURCE_DIR}"
  WORKING_DIRECTORY
    "${app_SOURCE_DIR}"
  OUTPUT_FILE
    "${app_BINARY_DIR}/Sources.cmake"
)
include("${app_BINARY_DIR}/Sources.cmake")

# Uncomment and configure below to include icons
#if(SFML_PLATFORM STREQUAL "osx")
  #set(_ICON_FILE "${CMAKE_SOURCE_DIR}/sites/${SAGE_SKIN_NAME}/icons/osx/icon.icns")

  # Add the icon to the sources.
  #list(APPEND "sfml_demo_SOURCES" "${_ICON_FILE}")

  # Specify the location where we want to put the icon.
  #set_source_files_properties("${_ICON_FILE}" PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

  #set(MACOSX_BUNDLE_ICON_FILE "icon.icns")
#endif()

# Executable: poker_app
# ------------------------------------------------------------------------------

include_directories("include")

if(SFML_PLATFORM STREQUAL "android")
  add_library("app" STATIC ${app_SOURCES})
  target_link_libraries("app" "android" "log" "EGL" "GLESv1_CM")
else()
  add_executable("app" WIN32 MACOSX_BUNDLE ${app_SOURCES})
  set_target_properties("app" PROPERTIES OUTPUT_NAME "app")
endif()

if(SAGE_PLATFORM STREQUAL "android")

endif()

target_link_libraries("app"
  "core"

  "sfml-graphics"
  "sfml-window"
  "sfml-system"
  "sfml-audio"

)

if(SFML_PLATFORM STREQUAL "android")
  # On Android we set sfml-main as a dependency, but we don't link it to the target.
  add_dependencies("app" "sfml-main")
endif()

if(SFML_PLATFORM STREQUAL "win32")
  target_link_libraries("app" "opengl32.lib")
endif()

if(SFML_PLATFORM STREQUAL "osx")

  if(0)
    set(CMAKE_SKIP_INSTALL_RPATH on)
    set(CMAKE_SKIP_RPATH on)

    set(CMAKE_INSTALL_NAME_DIR "@executable_path")
    set(CMAKE_BUILD_WITH_INSTALL_RPATH on)

    # Set the RPATH on the executable.
    add_custom_command(
      TARGET "app"
      POST_BUILD
      COMMAND
        "install_name_tool"
        "-add_rpath"
        "@loader_path"
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/\${CONFIGURATION}/${SFML_APP_NAME}.app/Contents/MacOS/${SFML_APP_NAME}"
      )
  endif()

  # Compile the iconset into an icns file.
  add_custom_command(
    TARGET "app"
    PRE_BUILD
    COMMAND
      "iconutil" "-c" "icns" "icon.iconset"
    WORKING_DIRECTORY
      "${CMAKE_SOURCE_DIR}/sites/${SFML_SKIN_NAME}/icons/osx/"
  )

  set_target_properties(
    "app"
      PROPERTIES
        MACOSX_BUNDLE_INFO_PLIST
          "${CMAKE_SOURCE_DIR}/cmake/MacOSXBundleInfo.plist.in"
  )
endif()

set_property(TARGET "app" PROPERTY FOLDER "Applications")
