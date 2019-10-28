project(42_fem2d_linearsolid)
cmake_minimum_required(VERSION 2.8)

if(MSVC)
set(CMAKE_CXX_FLAGS "/W4 /wd4100 /wd4458 /wd4577 /wd4267 /wd4244 /wd4800 /wd4996 /wd4530 /wd4245 /wd4505 /wd4838 /wd4305 /wd4505 /wd4456 -O2 -std=c++11")
else()
set( CMAKE_CXX_FLAGS "-Wall  -Wno-deprecated-declarations -std=c++11" )
endif()

set(DELFEM2_INCLUDE_DIR "../../src_cpp/include")
set(DELFEM2_SRC         "../../src_cpp/cpp")
set(DELFEM2_INC         "../../src_cpp/include/delfem2")

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(
  ${OPENGL_INCLUDE_DIR}
  ${GLUT_INCLUDE_DIR}
  ${DELFEM2_INCLUDE_DIR}
)

add_executable(${PROJECT_NAME}
  ${DELFEM2_INC}/vec2.h          ${DELFEM2_SRC}/vec2.cpp              
  ${DELFEM2_INC}/msh.h           ${DELFEM2_SRC}/msh.cpp              
  ${DELFEM2_INC}/mshtopo.h       ${DELFEM2_SRC}/mshtopo.cpp        
  ${DELFEM2_INC}/dtri.h          ${DELFEM2_SRC}/dtri.cpp         
  ${DELFEM2_INC}/mats.h          ${DELFEM2_SRC}/mats.cpp    
  ${DELFEM2_INC}/emat.h          ${DELFEM2_SRC}/emat.cpp     
  ${DELFEM2_INC}/camera.h        ${DELFEM2_SRC}/camera.cpp
  ${DELFEM2_INC}/color.h         ${DELFEM2_SRC}/color.cpp

  ${DELFEM2_INC}/dtri_v2.h       ${DELFEM2_SRC}/dtri_v2.cpp
  ${DELFEM2_INC}/ilu_mats.h      ${DELFEM2_SRC}/ilu_mats.cpp       
  ${DELFEM2_INC}/fem_emats.h     ${DELFEM2_SRC}/fem_emats.cpp                      

  ${DELFEM2_INC}/gl24_funcs.h    ${DELFEM2_SRC}/gl24_funcs.cpp
  ${DELFEM2_INC}/gl4_funcs.h     ${DELFEM2_SRC}/gl4_funcs.cpp
  ${DELFEM2_INC}/gl4_mshcolor.h  ${DELFEM2_SRC}/gl4_mshcolor.cpp

  ../glad4/include/glad/glad.h   ../glad4/src/glad.c
  ../glfw_cam.h

  main.cpp
)

set(GLAD_INCLUDE_DIR "../glad4/include")
get_filename_component(GLAD_INCLUDE_DIR ${GLAD_INCLUDE_DIR} ABSOLUTE)

# compile as "cmake -DEMSCRIPTEN=1 ."  to build with Emscripten

option(EMSCRIPTEN "Use Emscripten:" OFF)
if (NOT EMSCRIPTEN)
  set(GLFW_DIR "../glfw")
  get_filename_component(GLFW_DIR ${GLFW_DIR} ABSOLUTE)
  find_package(OpenGL REQUIRED)
  include_directories(
    ${OPENGL_INCLUDE_DIR}
    ${GLAD_INCLUDE_DIR}
    ${GLFW_DIR}/include
    ${DELFEM2_INCLUDE_DIR}
  )
  IF(APPLE)
    set(CMAKE_CXX_FLAGS "-Wall -Wno-deprecated-declarations -g")
    find_library( COCOA_LIBRARY Cocoa )
    find_library( OpenGL_LIBRARY OpenGL )
    find_library( IOKIT_LIBRARY IOKit )
    find_library( COREVIDEO_LIBRARY CoreVideo )
    target_link_libraries(${PROJECT_NAME}
      ${OPENGL_LIBRARY}
      ${GLFW_DIR}/src/libglfw3.a
      ${COCOA_LIBRARY} ${OpenGL_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY}
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
    if(CMAKE_CL_64)
      target_link_libraries(${PROJECT_NAME}
        ${OPENGL_LIBRARY}
        ${GLFW_DIR}/buildVS64/src/Release/glfw3.lib
        ${EXTRA_LIBS}
      )
    else()
        target_link_libraries(${PROJECT_NAME}
        ${OPENGL_LIBRARY}
        ${GLFW_DIR}/buildVS32/src/Release/glfw3.lib
        ${EXTRA_LIBS}
      )
    endif()
  endif()
else()
  set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE BOTH)
  set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
  set(CMAKE_C_COMPILER "emcc")
  set(CMAKE_CXX_COMPILER "em++")
  target_compile_definitions(${PROJECT_NAME} PUBLIC -DEMSCRIPTEN=1)
  set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-s USE_GLFW=3 -s USE_WEBGL2=1 -s FULL_ES3=1")
#  set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-s USE_GLFW=3 -s FULL_ES3=1")
  include_directories(
    ${GLAD_INCLUDE_DIR}
    ${DELFEM2_INCLUDE_DIR}
  )
endif()
