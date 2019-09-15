project(offscreen)
cmake_minimum_required(VERSION 2.8)

if(MSVC)
set(CMAKE_CXX_FLAGS "/W4 /wd4100 /wd4458 /wd4577 /wd4267 /wd4244 /wd4800 /wd4996 /wd4530 /wd4245 /wd4505 /wd4838 /wd4305 /wd4505 /wd4456 -O2 -std=c++11")
else()
set(CMAKE_CXX_FLAGS "-Wall  -Wno-deprecated-declarations -g" )
endif()

set(DELFEM2_INCLUDE_DIR "../../src_cpp/include")
set(DELFEM2_SRC         "../../src_cpp/cpp")
set(DELFEM2_INC         "../../src_cpp/include/delfem2")


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
include_directories(
  ${OPENGL_INCLUDE_DIR}
  ${GLUT_INCLUDE_DIR}
  ${GLEW_INCLUDE_DIR}
  ${DELFEM2_INCLUDE_DIR}
)

add_executable(${PROJECT_NAME}
  ${DELFEM2_INC}/vec2.h             ${DELFEM2_SRC}/vec2.cpp
  ${DELFEM2_INC}/vec3.h             ${DELFEM2_SRC}/vec3.cpp
  ${DELFEM2_INC}/mat3.h             ${DELFEM2_SRC}/mat3.cpp
  ${DELFEM2_INC}/quat.h             ${DELFEM2_SRC}/quat.cpp

  ${DELFEM2_INC}/v23m3q.h           ${DELFEM2_SRC}/v23m3q.cpp

  ${DELFEM2_INC}/gl_gpusampler.h    ${DELFEM2_SRC}/gl_gpusampler.cpp
  ${DELFEM2_INC}/gl_funcs.h         ${DELFEM2_SRC}/gl_funcs.cpp
  ${DELFEM2_INC}/gl_v3color.h       ${DELFEM2_SRC}/gl_v3color.cpp
  ${DELFEM2_INC}/gl_v23.h           ${DELFEM2_SRC}/gl_v23.cpp
  ${DELFEM2_INC}/gl_camera.h        ${DELFEM2_SRC}/gl_camera.cpp
  ${DELFEM2_INC}/glew_funcs.h       ${DELFEM2_SRC}/glew_funcs.cpp
  ${DELFEM2_SRC}/gl_color.cpp       ${DELFEM2_INC}/gl_color.h
  main.cpp
)

target_link_libraries(${PROJECT_NAME} 
  ${GLUT_LIBRARY}
  ${GLEW_LIBRARY}
  ${OPENGL_LIBRARY}
)