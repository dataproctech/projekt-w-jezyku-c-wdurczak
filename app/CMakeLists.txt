cmake_minimum_required(VERSION 3.10)
project(tictactoe3 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

find_package(PkgConfig REQUIRED)

pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)

find_package(CURL REQUIRED)

include_directories(
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_MIXER_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        /opt/homebrew/include
)

link_directories(
        ${SDL2_LIBRARY_DIRS}
        ${SDL2_MIXER_LIBRARY_DIRS}
        ${SDL2_IMAGE_LIBRARY_DIRS}
        /opt/homebrew/lib
)

add_executable(tictactoe3
        src/main.c
        src/game.c
        src/render.c
        src/api_client.c
)

target_compile_options(tictactoe3 PRIVATE
        ${SDL2_CFLAGS_OTHER}
        ${SDL2_MIXER_CFLAGS_OTHER}
        ${SDL2_IMAGE_CFLAGS_OTHER}
)

target_link_libraries(tictactoe3 PRIVATE
        ${SDL2_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        CURL::libcurl
        cjson
)