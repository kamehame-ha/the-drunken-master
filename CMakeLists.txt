cmake_minimum_required(VERSION 3.29)
project(drunken-master)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM
)
FetchContent_MakeAvailable(SFML)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 11.1.4
)
FetchContent_MakeAvailable(fmt)
add_executable(drunken-master main.cpp
        src/Wrapper.cpp
        src/Wrapper.h
        src/Game.cpp
        src/Game.h
        src/Text.cpp
        src/Text.h
        src/Window.cpp
        src/Window.h
        src/utils/GameState.cpp
        src/utils/GameState.h
        src/MainMenu.cpp
        src/MainMenu.h
        src/Player.cpp
        src/Player.h
        src/Hitbox.cpp
        src/Hitbox.h
        src/utils/Delay.cpp
        src/utils/Delay.h
)
target_link_libraries(drunken-master  PRIVATE SFML::Graphics SFML::Audio SFML::System fmt)