cmake_minimum_required(VERSION 4.1.1)
project(ObjectOcclusion)

find_package(SFML COMPONENTS Graphics Window System REQUIRED)


add_executable(${PROJECT_NAME} src/main.cpp src/visuals.cpp src/calculate_occlusion.cpp src/box_gen.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)