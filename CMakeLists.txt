cmake_minimum_required(VERSION 3.16)
project(ShapeBuilder)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMAND ON) # GET RID OF ERROR FLAGS IN CPP

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(ShapeBuilder 
    src/main.cpp
    src/Camera.cpp
    src/input/Mouse.cpp
    src/input/Keyboard.cpp
    src/shapes/Block.cpp
    src/ball/Ball.cpp
    src/ui/Dialog.cpp
    src/audio/AudioManager.cpp
    src/shapes/ShapeManager.cpp
    src/physics/Physics.cpp
)

target_include_directories(ShapeBuilder PRIVATE src -Wall -Wextra)
target_link_libraries(
    ShapeBuilder 
    sfml-graphics 
    sfml-window 
    sfml-system 
    sfml-audio
)
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
