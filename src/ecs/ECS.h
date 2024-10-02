//
// Created by vitor on 9/30/24.
//

#ifndef ECS_H
#define ECS_H
#include "Component.h"
#include "Entity.h"
#include "player.h"
#include "System.h"
#include "../util/Camera.h"


namespace pk {

    class ECS {

    private:
        static std::unordered_map<pk::TiledMapId, std::unique_ptr<pk::ECS>> ecsInstanceMap;

    public:
        static void createInstance(pk::TiledMapId mapId);
        static void deleteInstance(pk::TiledMapId mapId);
        static pk::ECS* getInstance(pk::TiledMapId mapId);
        static void updateInstance(pk::TiledMapId mapId, float dt);
        static void drawInstance(pk::TiledMapId mapId);
        static void deleteAllInstances();

    private:
        std::unique_ptr<pk::EntityManager> entity{};
        std::unique_ptr<pk::ComponentManager> component{};
        std::unique_ptr<pk::SystemManager> system{};

        std::unique_ptr<pk::Camera> camera{};
        std::vector<Rectangle> staticCollisions{};

        std::queue<pk::entity_t> entitiesToDestroy{};
        bool shouldDestroyAllEntities{};
        const pk::TiledMapId mapId;

        pk::player_info_t playerInfo{};

        void loadPlayer() {
            this->playerInfo.playerEntity = this->entityCreate(pk::PLAYER_ZINDEX, true);
            this->playerInfo.shadowEntity = this->entityCreate(pk::PLAYER_SHADOW_ZINDEX, GRAPHICS_PATH "other/shadow.png");
            this->addComponent<pk::sprite_animation_t, id::sprite_animation>(
                this->playerInfo.playerEntity,
                pk::sprite_animation_t{pk::PLAYER_SPRITE_ANIMATION}
            );
            pk::transform_t& t = this->getTransform(this->playerInfo.playerEntity);
            t.pos = pk::PLAYER_START_POS[this->mapId];
            t.size = Vector2{pk::PLAYER_SIZE, pk::PLAYER_SIZE};
            this->playerInfo.collisionRect = Rectangle{
                t.pos.x + t.size.x / 2.0f - pk::TILE_SIZE / 2.0f,
                t.pos.y + t.size.y - pk::TILE_SIZE,
                pk::TILE_SIZE,
                pk::TILE_SIZE
            };
        }

        void loadTiledMap() {
            const pk::tiled_map_t& tiledMap = pk::TILED_MAP[this->mapId];

            std::string line{};
            std::ifstream file(tiledMap.txtFile);
            assert(file.is_open());

            int n, i;
            float x, y, width, height;
            this->createSprite(0, tiledMap.worldImage);

            while (file >> line) {
                file >> n;
                if (line == "Collision") {
                    for (i = 0; i < n; i++) {
                        file >> x >> y >> width >> height;
                        this->addCollision(x, y, width, height);
                    }
                    continue;
                }
                if (line == "Entities") {

                }

            }

            file.close();
        }

        explicit ECS(const pk::TiledMapId mapId) : mapId(mapId) { }

        void init() {
            this->entity = std::make_unique<pk::EntityManager>(this->mapId);
            this->component = std::make_unique<pk::ComponentManager>(this->mapId);
            this->system = std::make_unique<pk::SystemManager>(this->mapId);
            this->camera = std::make_unique<pk::Camera>(mapId, this->mapId);
            this->staticCollisions.reserve(2048);
            this->loadTiledMap();
            this->loadPlayer();
        }

    public:

        pk::entity_t entityCreate(const pk::zindex_t zindex, const bool isOnCamera) {
            const pk::entity_t e = this->entity->entityCreate();
            this->component->insert<pk::transform_t, pk::id::transform>(e, pk::transform_t{zindex});
            if (isOnCamera) this->camera->insert(e);
            return e;
        }

        pk::entity_t createSprite(const pk::zindex_t zindex, const char* fileName) {
            const pk::entity_t e = this->entityCreate(zindex, true);
            this->addComponent<pk::sprite_t, pk::id::sprite>(e, pk::sprite_t{fileName});
            const pk::sprite_t& sprite = this->component->at<pk::sprite_t, pk::id::sprite>(e);
            pk::transform_t& transform = this->getTransform(e);
            transform.size = Vector2{
                static_cast<float>(sprite.texture.width),
                static_cast<float>(sprite.texture.height)
            };
            return e;
        }

        void addCollision(const float x, const float y, const float width, const float height) {
            this->staticCollisions.emplace_back(Rectangle{x, y, width, height});
        }

        bool checkCollision(const Rectangle& rect) {
            return std::any_of(
                this->staticCollisions.begin(),
                this->staticCollisions.end(),
                [rect](const Rectangle& r) {
                    return CheckCollisionRecs(rect, r);
                }
            );
        }

        template<typename T, pk::component_t id>
        void addComponent(const pk::entity_t e, T c) {
            this->component->insert<T, id>(e, std::move(c));
            this->system->insert(e, id);
        }

        template<typename T, pk::component_t id>
        T& getComponent(const pk::entity_t e) {
            return this->component->at<T, id>(e);
        }

        pk::transform_t& getTransform(const pk::entity_t e) {
            return this->component->at<pk::transform_t, pk::id::transform>(e);
        }

        void entityDestroy(const pk::entity_t e) {
            this->entitiesToDestroy.push(e);
        }

        void update(const float dt) {
            this->camera->handleUserInput();
            this->system->update(dt);

            if (this->shouldDestroyAllEntities) {
                this->shouldDestroyAllEntities = false;
                this->unloadAllEntities();
            }

            while (this->entitiesToDestroy.empty() == false) {
                const pk::entity_t e = this->entitiesToDestroy.front();
                this->entitiesToDestroy.pop();
                this->camera->erase(e);
                this->entity->entityDestroy(e);
                this->component->entityDestroy(e);
                this->system->entityDestroy(e);
            }
        }

        void draw() const {
            this->camera->draw(this->system.get());
        }

        void unloadAllEntities() {
            this->camera->clear();
            this->entity->clear();
            this->component->clear();
            this->system->clear();
            this->staticCollisions.clear();
            this->entitiesToDestroy = std::queue<pk::entity_t>();
        }

        void clear() {
            this->shouldDestroyAllEntities = true;
        }

        pk::Camera* getCamera() const {
            return this->camera.get();
        }

        pk::TiledMapId getMapId() const {
            return this->mapId;
        }

        pk::player_info_t* getPlayerInfo() {
            return &this->playerInfo;
        }

    };

}

#endif //ECS_H
