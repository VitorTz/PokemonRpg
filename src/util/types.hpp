#pragma once
#include <cstddef>
#include <unordered_map>
#include <typeinfo>
#include <cstdint>


namespace pk {


    typedef std::uint32_t entity_t;
    typedef std::uint8_t component_t;
    typedef std::uint8_t zindex_t;

    enum MapId {
        WorldMapID = 0,
        NumMaps
    };

    typedef struct tiled_map {
        const char* fileName{};
        pk::MapId mapId{};
        int rows{};
        int cols{};
    } tiled_map_t;

    typedef struct sprite_animation_info {
        const char* fileName{};
        std::uint8_t rows{};
        std::uint8_t cols{};
        std::uint8_t speed{};
        std::uint8_t maxFrame{};
    } sprite_animation_info_t;

    class TypeId {

        private:
            std::unordered_map<const char*, pk::component_t> idMap{};

        public:
            template<typename T>
            void registerType() {
                this->idMap.emplace(typeid(T).name(), this->idMap.size());
            }

            template<typename T>
            pk::component_t get() {
                return this->idMap[typeid(T).name()];
            }

            std::size_t size() const {
                return this->idMap.size();
            }

    };

    enum SceneId {
        LevelSceneId = 0,
        TitleScreenId,
        TestScene1Id,
        LoadingSceneId,
        NumScenes
    };


}