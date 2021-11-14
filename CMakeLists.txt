cmake_minimum_required(VERSION 3.20)

project(my_box)

file(GLOB files ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include 
                    ${CMAKE_CURRENT_SOURCE_DIR}/resources/glm/glm
                    ${CMAKE_CURRENT_SOURCE_DIR}/resources/glm/glm/gtc 
                    )

add_executable(my_box ${files})

target_link_libraries(my_box PUBLIC glfw GL GLEW)

