cmake_minimum_required(VERSION 3.25)

find_package(SDL3 CONFIG REQUIRED)

add_library(engine STATIC
        src/core/Engine.cpp
        src/graphics/SDL3Renderer.cpp
        src/graphics/Window.cpp
)

target_include_directories(engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(engine PUBLIC
        project_sanitizers
        project_warnings
        SDL3::SDL3
)

target_compile_features(engine PUBLIC cxx_std_20)