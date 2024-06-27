# CMakeList.txt : CMake project for PokemonRpg, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("PokemonRpg")

add_subdirectory(./lib/raylib)

# Add source to this project's executable.
add_executable (PokemonRpg "Pokemon.cpp" "include/pokemon.h"   "include/util.h" "src/util.cpp" "include/scene.h" "include/scene_manager.h" "src/scene_manager.cpp" "src/scene_title_screen.cpp" "src/scene_level.cpp" "include/component.h" "include/texture_pool.h" "src/texture_pool.cpp" "include/component_array.h" "include/component_manager.h" "include/ecs.h" "include/entity_manager.h" "src/entity_manager.cpp" "include/system.h" "include/system_manager.h" "src/system_transform.cpp" "src/system_sprite.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET PokemonRpg PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(${PROJECT_NAME} raylib)

# Setting ASSETS_PATH
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/") # dev
#target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="./assets/") # assets folder is in the same directory as the game executable

# TODO: Add tests and install targets if needed.