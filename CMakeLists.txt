cmake_minimum_required(VERSION 3.16)
project(spaceinvaders)

# Use modern C++.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Put built binaries/libraries in the build config folder.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# Build SDL from the local SDL folder in this repo.
add_subdirectory(SDL EXCLUDE_FROM_ALL)


# Main game executable.
# Add all .cpp files that should be compiled into the game.
add_executable(spaceinvaders WIN32
    main.cpp
    Engine.cpp
    TitleScene.cpp
    PlayScene.cpp
    CreditScene.cpp
    Player.cpp
    GameObject.cpp
    Projectile.cpp
    Enemy.cpp
)

# Link SDL3 to the game.
target_link_libraries(spaceinvaders PRIVATE SDL3::SDL3)
