cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
project( detector )
find_package( OpenCV REQUIRED )
add_executable( detector detector.cpp )
target_link_libraries( detector ${OpenCV_LIBS} )
