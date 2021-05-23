cmake_minimum_required(VERSION 3.19)
project(opencv_kadai1)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV 4.5.2 REQUIRED PATHS "C:/opencv/opencv-4.5.2/build")
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(opencv_kadai1 main.cpp)

target_link_libraries( opencv_kadai1 ${OpenCV_LIBS} )