#include "include/PokemonRpg.h"


int main() {
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(POKE_SCREEN_WIDTH, POKE_SCREEN_HEIGHT, POKE_WINDOW_TITLE);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLUE);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
