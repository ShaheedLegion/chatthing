
if(SFML_PLATFORM STREQUAL "linux")

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
  set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -m32")
  set(CMAKE_CXX_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m32")
  set(CMAKE_CXX_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -m32")
  set(CMAKE_CXX_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -m32")

endif(SFML_PLATFORM STREQUAL "linux")
