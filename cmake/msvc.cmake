
if(MSVC)

  message(STATUS "MSVC: Mapping memory leaks.")
  add_definitions("-D_CRTDBG_MAP_ALLOC")

  message(STATUS "MSVC: Enable variadic tuples for Visual Studio 2012.")
  add_definitions("-D_VARIADIC_MAX=10")

  message(STATUS "MSVC: Enable multi-processor compilation.")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")

  message(STATUS "MSVC: Enable use full paths.")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /FC")

  # Default to statically-linked runtime.
  set(MSVC_RUNTIME "dynamic" CACHE STRING "Use dynamic or static runtime (dynamic/static)")
  # Set compiler options.
  set(variables
    CMAKE_C_FLAGS_DEBUG
    CMAKE_C_FLAGS_MINSIZEREL
    CMAKE_C_FLAGS_RELEASE
    CMAKE_C_FLAGS_RELWITHDEBINFO
    CMAKE_CXX_FLAGS_DEBUG
    CMAKE_CXX_FLAGS_MINSIZEREL
    CMAKE_CXX_FLAGS_RELEASE
    CMAKE_CXX_FLAGS_RELWITHDEBINFO
  )
  if(${MSVC_RUNTIME} STREQUAL "static")
    message(STATUS "MSVC: Forcing use of statically-linked runtime.")
    foreach(variable ${variables})
      if(${variable} MATCHES "/MD")
        string(REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
      endif()
    endforeach()
  else()
    message(STATUS "MSVC: Forcing use of dynamically-linked runtime.")
    foreach(variable ${variables})
      if(${variable} MATCHES "/MT")
        string(REGEX REPLACE "/MT" "/MD" ${variable} "${${variable}}")
      endif()
    endforeach()
  endif()

endif(MSVC)
