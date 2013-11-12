cmake_minimum_required (VERSION 2.6)

project (silence)
set (silence_VERSION_MAJOR 0)
set (silence_VERSION_MINOR 1)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")

if (UNIX)
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif ()
if (APPLE)
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif ()

add_executable (silence
	src/GLWindow.h
	src/GLWindow.cc
	src/main.cc
	)

find_package (GLM REQUIRED)
include_directories (${GLM_INCLUDE_DIRS})

find_package (GLEW REQUIRED)
include_directories (${GLEW_INCLUDE_DIRS})
target_link_libraries (silence ${GLEW_LIBRARIES})

find_package (GLFW REQUIRED)
include_directories (${GLFW_INCLUDE_DIR})
target_link_libraries (silence ${GLFW_LIBRARIES})

find_package(OpenGL REQUIRED)
if (NOT APPLE)
	include_directories (${OPENGL_INCLUDE_DIR})
endif ()
target_link_libraries (silence ${OPENGL_LIBRARIES})
