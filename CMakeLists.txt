cmake_minimum_required(VERSION 3.8)
project(PokemonRpg LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON)
FetchContent_MakeAvailable(SFML)


add_executable (${PROJECT_NAME}
        src/main.cpp
        src/pokemon.h
        src/window/Camera.h
        src/window/Camera.cpp
        src/ecs/EntityManager.h
        src/ecs/EntityManager.cpp
        src/ecs/System.h
        src/ecs/SystemManager.h
        src/TypeId.h
        src/ecs/components.h
        src/util/TexturePool.h
        src/util/TexturePool.cpp
        src/util/util.h
        src/util/util.cpp
        src/ecs/ComponentArray.h
        src/ecs/ComponentManager.h
        src/ecs/ECS.h
        src/scene/Scene.h
        src/scene/SceneManager.cpp
        src/scene/TestScene1.cpp
        src/scene/LevelScene.cpp
        src/scene/LoadingScreen.cpp
        src/scene/TitleScreen.cpp
        src/ecs/SystemTransform.cpp
        src/ecs/SystemSprite.cpp
        src/ecs/SystemCollisionBox.cpp
        src/ecs/SystemCollisionBoxStatic.cpp
        src/ecs/SystemWater.cpp
        src/ecs/SystemBezierCurve.cpp
        src/window/Window.h
        src/window/Window.cpp
        src/ecs/SystemBoat.cpp
        src/ecs/SystemSpriteAnimation.cpp
        src/util/FrameCounter.h
        src/util/FrameCounter.cpp
        src/ecs/player.h
        src/ecs/player.cpp
        src/ecs/SystemPlayer.cpp
        src/util/Debug.h
        src/util/Debug.cpp
        src/util/FontPool.h
        src/util/FontPool.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)


target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:-Wall -Wextra -pedantic -g>
    $<$<CONFIG:Release>:-O3 -DNDEBUG>
    $<$<CONFIG:RelWithDebInfo>:-O2 -g>
    $<$<CONFIG:MinSizeRel>:-Os>
)

if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM)
endif()

# Setting ASSETS_PATH
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/") # Set the asset path macro to the absolute path on the dev machine
#target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="./assets") # Set the asset path macro in release mode to a relative path that assumes the assets folder is in the same directory as the game executable
