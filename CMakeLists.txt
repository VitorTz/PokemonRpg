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
        src/util/util.h
        src/util/util.cpp
        src/util/AssetPool.h
        src/util/TexturePool.cpp
        src/util/FontID.h
        src/util/FontPool.cpp
        src/scene/Scene.h
        src/scene/SceneID.h
        src/scene/SceneManager.cpp
        src/scene/Level.cpp
        src/scene/TitleScreen.cpp
        src/scene/LoadingScreen.cpp
        src/ecs/components.h
        src/util/types.h
        src/util/FrameCounter.h
        src/util/FrameCounter.cpp
        src/util/TypeID.h
        src/ecs/Entity.h
        src/ecs/EntityManager.cpp
        src/ecs/System.h
        src/ecs/Component.h
        src/ecs/ECS.h
        src/util/Camera.h
        src/util/Camera.cpp
        src/scene/TestScene.cpp
        src/ecs/SpriteSystem.cpp
        src/ecs/MovementSystem.cpp
        src/ecs/SpriteAnimationSystem.cpp
        src/ecs/CollisionSystem.cpp
        src/ecs/PlayerSystem.cpp
        src/util/TiledMap.h
        src/util/TiledMap.cpp

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
