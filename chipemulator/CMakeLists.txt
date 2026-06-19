cmake_minimum_required(VERSION 3.10)
project(chipemulator CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(chipemulator main.cpp)

if(UNIX AND NOT APPLE)
    target_link_libraries(chipemulator PRIVATE raylib GL m pthread dl rt X11)
elseif(APPLE)
    target_link_libraries(chipemulator PRIVATE raylib)
elseif(WIN32)
    target_link_libraries(chipemulator PRIVATE raylib winmm gdi32)
endif()
