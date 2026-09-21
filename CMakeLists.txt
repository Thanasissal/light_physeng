cmake_minimum_required(VERSION 4.1)
project(light_physeng)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm
        GIT_TAG 1.0.3
)
FetchContent_MakeAvailable(glm)

find_package(OpenGL REQUIRED)

add_executable(light_physeng main.cpp
        Camera.cpp
        glad.c
        Camera.h
        Math.h
        Shader.h
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

