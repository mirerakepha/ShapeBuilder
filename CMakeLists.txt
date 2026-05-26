cmake_minimum_required(VERSION 3.16)
project(ShapeBuilder)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMAND ON) # GET RID OF ERROR FLAGS IN CPP

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(ShapeBuilder src/main.cpp)
target_link_libraries(ShapeBuilder sfml-graphics sfml-window sfml-system)
