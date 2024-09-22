//
// Created by vitor on 9/21/24.
//

#ifndef SCENEID_H
#define SCENEID_H

namespace pk {

    enum SceneId {
        TitleScreenId,
        LevelSceneId,
        LoadingScreenId,
        TestScene1Id
    };

    constexpr pk::SceneId MAIN_SCENE{pk::TestScene1Id};

}

#endif //SCENEID_H
