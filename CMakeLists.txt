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
        src/Camera.h
        src/Camera.cpp
        src/ecs/EntityManager.h
        src/ecs/EntityManager.cpp
        src/ecs/System.h
        src/ecs/SysteManager.h
        src/TypeId.h
        src/ecs/components.h
        src/TexturePool.h
        src/TexturePool.cpp
        src/util.h
        src/util.cpp
        src/ecs/ComponentArray.h
        src/ecs/ComponentArray.cpp
        src/ecs/ComponentManager.h
        src/ecs/ECS.h)
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
