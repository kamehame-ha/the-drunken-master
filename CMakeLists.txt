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
        src/utils/Wrapper.cpp
        src/utils/Wrapper.h
        src/Game.cpp
        src/Game.h
        src/utils/Text.cpp
        src/utils/Text.h
        src/utils/Window.cpp
        src/utils/Window.h
        src/utils/GameState.cpp
        src/utils/GameState.h
        src/game_utils/MainMenu.cpp
        src/game_utils/MainMenu.h
        src/entity/Player.cpp
        src/entity/Player.h
        src/map_utils/Hitbox.cpp
        src/map_utils/Hitbox.h
        src/utils/Delay.h
        src/map_utils/Map.cpp
        src/map_utils/Map.h
        src/map_utils/map_elements/Element.cpp
        src/map_utils/map_elements/Element.h
        src/map_utils/map_elements/Ground.h
        src/map_utils/map_elements/Platform.h
        src/map_utils/map_elements/Exit.h
        src/map_utils/map_elements/Box.h
        src/map_utils/map_elements/Spikes.h
        src/level_utils/LevelParser.cpp
        src/level_utils/LevelParser.h
        src/map_utils/map_elements/Start.h
        src/level_utils/LevelInterface.h
        src/save_utils/GameSave.cpp
        src/save_utils/GameSave.h
        src/game_utils/Dice.h
)
target_link_libraries(drunken-master  PRIVATE SFML::Graphics SFML::Audio SFML::System fmt)