cmake_minimum_required(VERSION 3.5)
project(image2ascii)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp
        argument-parser.cpp
        argument-parser.h
)

add_executable(image2ascii ${SOURCE_FILES})

add_definitions( -DMAGICKCORE_QUANTUM_DEPTH=16 )
add_definitions( -DMAGICKCORE_HDRI_ENABLE=0 )

find_package(ImageMagick COMPONENTS Magick++)

include_directories(${ImageMagick_INCLUDE_DIRS})
target_link_libraries(image2ascii ${ImageMagick_LIBRARIES})
