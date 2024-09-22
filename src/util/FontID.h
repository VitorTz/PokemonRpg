//
// Created by vitor on 9/21/24.
//

#ifndef FONTID_H
#define FONTID_H
#include <string>

namespace pk {

    enum FontID {
        Light,
        Regular,
        Bold
    };

    constexpr const char* FONT_PATH[3] = {
        ASSETS_PATH "font/Lato/Lato-Light.ttf",
        ASSETS_PATH "font/Lato/Lato-Regular.ttf",
        ASSETS_PATH "font/Lato/Lato-Bold.ttf"
    };

}

#endif //FONTID_H
