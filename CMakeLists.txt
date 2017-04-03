cmake_minimum_required(VERSION 2.8)

project(repka)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-deprecated")

include_directories(. graphics core players units)

file(GLOB SRCS ./*.cpp)
add_executable(repka ${SRCS})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS}  )
target_link_libraries( _repka ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
