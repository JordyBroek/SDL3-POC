cmake_minimum_required(VERSION 3.25)

add_executable(Game
    src/main.cpp
)

target_link_libraries(Game PRIVATE engine)

target_link_libraries(Game PRIVATE
    project_sanitizers
    project_warnings
)

add_custom_command(TARGET Game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:Game>/assets
)

target_include_directories(Game PRIVATE ../engine)
target_link_directories(Game PRIVATE ../engine/cmake-build-debug)
