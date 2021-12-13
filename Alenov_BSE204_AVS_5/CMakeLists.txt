cmake_minimum_required(VERSION 3.20)

project(Alenov_BSE204_AVS_5)

set(CMAKE_CXX_STANDARD 17)
find_package (Threads)
add_executable(Alenov_BSE204_AVS_5 main.cpp Client.cpp Time.cpp Hairdresser.cpp)
target_link_libraries (Alenov_BSE204_AVS_5 ${CMAKE_THREAD_LIBS_INIT})