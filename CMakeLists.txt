cmake_minimum_required(VERSION 3.19)
project(opencv_image_processing)

set(CMAKE_CXX_STANDARD 14)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_subdirectory(src)

add_executable( cv_img_proc main.cpp )

target_link_libraries( cv_img_proc sources ${OpenCV_LIBS} )