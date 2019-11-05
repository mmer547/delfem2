project(201_dyntri2d_triangulation)
cmake_minimum_required(VERSION 2.8)


set(DELFEM2_INCLUDE_DIR "../../src_cpp/include")
set(DELFEM2_SRC         "../../src_cpp/cpp")
set(DELFEM2_INC         "../../src_cpp/include/delfem2")
add_definitions(-DPATH_INPUT_DIR="${PROJECT_SOURCE_DIR}/../../test_inputs")

set(GLFW_DIR "../../src_cpp/external/glfw")
get_filename_component(GLFW_DIR ${GLFW_DIR} ABSOLUTE)

find_package(OpenGL REQUIRED)
include_directories(
  ${OPENGL_INCLUDE_DIR}
  ${GLFW_DIR}/include
  ${DELFEM2_INCLUDE_DIR}
)

add_executable(${PROJECT_NAME}
  ${DELFEM2_INC}/vec2.h             ${DELFEM2_SRC}/vec2.cpp
  ${DELFEM2_INC}/vec3.h             ${DELFEM2_SRC}/vec3.cpp
  ${DELFEM2_INC}/dtri.h             ${DELFEM2_SRC}/dtri.cpp
  ${DELFEM2_INC}/camera.h           ${DELFEM2_SRC}/camera.cpp

  ${DELFEM2_INC}/dtri_v2.h          ${DELFEM2_SRC}/dtri_v2.cpp
                
  ${DELFEM2_INC}/opengl/gl2_funcs.h
  ${DELFEM2_INC}/opengl/gl2_funcs.cpp
  ${DELFEM2_INC}/opengl/gl2_v23.h
  ${DELFEM2_INC}/opengl/gl2_v23.cpp
  ${DELFEM2_INC}/opengl/gl2_v23dtricad.h
  ${DELFEM2_INC}/opengl/gl2_v23dtricad.cpp
  ${DELFEM2_INC}/opengl/glfw_viewer.hpp
  ${DELFEM2_INC}/opengl/glfw_viewer.cpp
  main.cpp
)

IF(APPLE)
  set(CMAKE_CXX_FLAGS "-Wall -Wno-deprecated-declarations -g")
  find_library( COCOA_LIBRARY Cocoa )
  find_library( IOKIT_LIBRARY IOKit )
  find_library( COREVIDEO_LIBRARY CoreVideo )
  target_link_libraries(${PROJECT_NAME}
    ${OPENGL_LIBRARY}
    ${GLFW_DIR}/src/libglfw3.a
    ${COCOA_LIBRARY}
    ${IOKIT_LIBRARY}
    ${COREVIDEO_LIBRARY}
  )
ELSEIF(UNIX)
  set(CMAKE_CXX_FLAGS "-Wall -Wno-deprecated-declarations -g")
  target_link_libraries(${PROJECT_NAME}
    ${OPENGL_LIBRARY}
    ${GLFW_DIR}/src/libglfw3.a
    -lrt -lm -ldl -lX11 -lpthread -lxcb -lXau -lXdmcp
  )
ELSEIF(MSVC)
  set(CMAKE_CXX_FLAGS "/W4 /wd4100 /wd4458 /wd4577 /wd4267 /wd4244 /wd4800 /wd4996 /wd4530 /wd4245 /wd4505 /wd4838 /wd4305 /wd4505 /wd4456 -O2 -std=c++11")
ENDIF()