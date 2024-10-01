//
// Created by vitor on 9/30/24.
//

#ifndef SYSTEM_H
#define SYSTEM_H
#include "../pokemon.h"


namespace pk {


    class SystemManager {

    public:
        std::unordered_map<pk::component_t, std::unordered_set<pk::entity_t>> component_to_entities{};
        std::unordered_map<pk::entity_t, std::unordered_set<pk::component_t>> entity_to_components{};
        std::map<pk::zindex_t, std::vector<std::pair<float, pk::entity_t>>> z_index_to_entities{};
        std::array<bool, pk::MAX_ENTITIES> onCameraEntities{};

    private:
        void update_sprite_animation(float dt);
        void update_movement(float dt);
        void update_player(float dt);

    private:
        static void sprite_draw(pk::entity_t e);
        static void sprite_animation_draw(pk::entity_t e);

    public:
        SystemManager();
        void addToCamera(pk::entity_t e);
        void rmvFromCamera(pk::entity_t e);
        void insert(pk::entity_t e, pk::component_t componentId);
        void erase(pk::entity_t e, pk::component_t componentId);
        void entityDestroy(pk::entity_t e);
        void update(float dt);
        void clear();
        void draw();

    };


}

#endif //SYSTEM_H
