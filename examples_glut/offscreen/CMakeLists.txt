cmake_minimum_required(VERSION 2.8)
project(offscreen)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
if(MSVC)
  set(CMAKE_CXX_FLAGS "/W4 /wd4100 /wd4458 /wd4577 /wd4267 /wd4244 /wd4800 /wd4996 /wd4530 /wd4245 /wd4505 /wd4838 /wd4305 /wd4505 /wd4456 -O2 -std=c++11")
else()
  set(CMAKE_CXX_FLAGS "-Wall  -Wno-deprecated-declarations -g" )
endif()

set(DELFEM2_INCLUDE_DIR "../../include")
set(DELFEM2_INC         "../../include/delfem2")

set(GLAD_INCLUDE_DIR "../glad3/include")
get_filename_component(GLAD_INCLUDE_DIR ${GLAD_INCLUDE_DIR} ABSOLUTE)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(
  ${OPENGL_INCLUDE_DIR}
  ${GLUT_INCLUDE_DIR}
  ${GLAD_INCLUDE_DIR}
  ${DELFEM2_INCLUDE_DIR}
)

add_executable(${PROJECT_NAME}
  ${DELFEM2_INC}/vec2.h                 ${DELFEM2_INC}/vec2.cpp
  ${DELFEM2_INC}/vec3.h                 ${DELFEM2_INC}/vec3.cpp
  ${DELFEM2_INC}/mat3.h                 ${DELFEM2_INC}/mat3.cpp
  ${DELFEM2_INC}/quat.h                 ${DELFEM2_INC}/quat.cpp
  ${DELFEM2_INC}/camera.h               ${DELFEM2_INC}/camera.cpp
  ${DELFEM2_INC}/color.h                ${DELFEM2_INC}/color.cpp
             
  ${DELFEM2_INC}/v23m3q.h               ${DELFEM2_INC}/v23m3q.cpp

  ${DELFEM2_INC}/opengl/gl_gpusampler.h ${DELFEM2_INC}/opengl/gl_gpusampler.cpp
  ${DELFEM2_INC}/opengl/gl_v3color.h    ${DELFEM2_INC}/opengl/gl_v3color.cpp
  ${DELFEM2_INC}/opengl/gl2_v23.h       ${DELFEM2_INC}/opengl/gl2_v23.cpp
  ${DELFEM2_INC}/opengl/gl2_color.cpp   ${DELFEM2_INC}/opengl/gl2_color.h
  ${DELFEM2_INC}/opengl/gl2_funcs.h     ${DELFEM2_INC}/opengl/gl2_funcs.cpp
  ${DELFEM2_INC}/opengl/gl2ew_funcs.h   ${DELFEM2_INC}/opengl/gl2ew_funcs.cpp
  
  ../glad3/include/glad/glad.h      ../glad3/src/glad.c

  main.cpp
)

IF(UNIX)
  target_link_libraries(${PROJECT_NAME}
    ${GLUT_LIBRARY}
    ${OPENGL_LIBRARY}
    -ldl
  )
ELSE()
  target_link_libraries(${PROJECT_NAME}
    ${GLUT_LIBRARY}
    ${OPENGL_LIBRARY}
  )
ENDIF()
