#pragma once
#include <array>
#include <cstddef>
#include <memory>
#include <cassert>
#include <unordered_map>
#include "../util/globals.hpp"
#include "../util/constants.hpp"
#include "../util/types.hpp"
#include "../util/FrameCounter.hpp"


namespace pk {

    constexpr std::size_t NUM_COMPONENTS{5};

    typedef struct transform {
        Vector2 pos{};
        Vector2 size{};
        pk::zindex_t zindex{};
        float rotation{};
        transform() = default;
        transform(const pk::zindex_t zindex) : zindex(zindex) { }
    } transform_t;


    typedef struct sprite {
        Texture2D texture{};
    } sprite_t;

    typedef struct sprite_animation {
        Texture2D texture{};
        Rectangle rect{};
        pk::FrameCounter counter;
        std::uint8_t cols{};
        sprite_animation(
            const pk::sprite_animation_info_t& source
        ) : texture(pk::gAssetPool.getTexture(source.fileName)),
            counter(source.maxFrame, source.speed),
            cols(source.cols) {

        }
    } sprite_animation_t;


    typedef struct collision {
        Rectangle rect{};
    } collision_t;

    typedef struct player {
        pk::entity_t playerEntity{};
        pk::entity_t shadowEntity{};
        Rectangle collisionRect{pk::PLAYER_COLLISION_RECT};
        Rectangle actionRect{pk::PLAYER_ACTION_RECT};
        char direction[2]{'i', 'd'};
        char action{'x'};
    } player_t; 


    class IComponentArray {

        public:
            virtual ~IComponentArray() = default;
            virtual void erase(pk::entity_t e) = 0;
            virtual void clear() = 0;
            virtual std::size_t size() const = 0;
    };


    template<typename T>
    class ComponentArray : public pk::IComponentArray {

        private:
            std::array<T, pk::MAX_ENTITIES> arr{};
            std::unordered_map<pk::entity_t, std::uint32_t> entityToIndex{};
            std::unordered_map<std::uint32_t, pk::entity_t> indexToEntity{};
            std::uint32_t mSize{};
        
        public: 
            ComponentArray<T>() {
                this->entityToIndex.reserve(pk::MAX_ENTITIES);
                this->indexToEntity.reserve(pk::MAX_ENTITIES);
            }

            void insert(const pk::entity_t e, T c) {
                this->entityToIndex[e] = this->mSize;
                this->indexToEntity[this->mSize] = e;
                this->arr[this->mSize++] = c;
            }

            void erase(const pk::entity_t e) override {
                if (this->entityToIndex.find(e) == this->entityToIndex.end()) {
                    return;
                }

                const std::uint32_t lastComponentIndex = this->mSize--;
                const std::uint32_t removedComponentIndex = this->entityToIndexe[e];
                const pk::entity_t lastEntity = this->indexToEntity[lastComponentIndex];

                this->entityToIndex[lastEntity] = removedComponentIndex;
                this->indexToEntity[removedComponentIndex] = lastEntity;

                this->arr[removedComponentIndex] = this->arr[lastComponentIndex];

                this->entityToIndex[lastEntity] = removedComponentIndex;
                this->indexToEntity[removedComponentIndex] = lastEntity;

                this->entityToIndex.erase(e);
                this->indexToEntity.erase(lastComponentIndex);
            }            

            inline T& at(const pk::entity_t e) {
                assert(this->entityToIndex.find(e) != this->entityToIndex.end());
                return this->arr[this->entityToIndex[e]];
            }

            void clear() override {
                this->entityToIndex.clear();
                this->indexToEntity.clear();
                this->mSize = 0;
            }

            std::size_t size() const override {
                return static_cast<std::size_t>(this->mSize);
            }

    };


    class ComponentManager {

        private:
            std::unordered_map<pk::component_t, std::unique_ptr<pk::IComponentArray>> componentMap{};

        public:
            
            template<typename T>
            void registerComponent() {  
                this->componentMap.emplace(pk::gTypeId.get<T>(), std::make_unique<pk::ComponentArray<T>>());
            }

            template<typename T>
            void insert(const pk::entity_t e, T c) {
                const pk::component_t id = pk::gTypeId.get<T>();
                dynamic_cast<pk::ComponentArray<T>*>(this->componentMap[pk::gTypeId.get<T>()].get())->insert(e, std::move(c));
            }

            template<typename T>
            void erase(const pk::entity_t e) {
                this->componentMap[pk::gTypeId.get<T>()]->erase(e);
            }

            template<typename T>
            inline T& at(const pk::entity_t e) {
                const pk::component_t id = pk::gTypeId.get<T>();
                dynamic_cast<pk::ComponentArray<T>*>(this->componentMap[pk::gTypeId.get<T>()].get())->at(e);
            }

            void entityDestroy(const pk::entity_t e) {
                for (auto& pair : this->componentMap) {
                    pair.second->erase(e);
                }
            }

            void clear() {
                for (auto& pair : this->componentMap) {
                    pair.second->clear();
                }
            }

            std::size_t numComponentArray() const {
                return this->componentMap.size();
            }

    };
 
}