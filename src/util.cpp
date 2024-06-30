#include "../include/util.h"


void poke::print_rect(const Rectangle& r) {
	printf("Rect(%.2f, %.2f, %.2f, %.2f)\n", r.x, r.y, r.width, r.height);
}


void poke::print_vec(const Vector2 v) {
	printf("Vec(%.2f, %.2f)\n", v.x, v.y);
}


unsigned long poke::hash(const char* s) {
    unsigned long hash = 5381;
    int i = 0;
    while (s[i] != '\0') {
        int c = s[i];
        hash = ((hash << 5) + hash) + c;
        i++;
    }
    return hash;
}


void poke::applyCharacterSpriteRect(Rectangle* rect, const char direction[2], const std::uint8_t currentSprite) {
    switch (direction[1]) {
        case 'l':
            rect->y = POKE_PLAYER_HEIGHT;
            break;
        case 'r':
            rect->y = POKE_PLAYER_HEIGHT * 2.0f;
            break;
        case 'u':
            rect->y = POKE_PLAYER_HEIGHT * 3.0f;
            break;
        case 'd':
            rect->y = 0.0f;
            break;
        default:
            break;
    }
    rect->x = direction[0] == 'i' ? 0.0f : currentSprite * POKE_PLAYER_WIDTH;
 }