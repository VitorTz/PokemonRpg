#include "../include/util.h"


void poke::print_rect(const Rectangle& r) {
	printf("Rect(%.2f, %.2f, %.2f, %.2f)\n", r.x, r.y, r.width, r.height);
}


void poke::print_vec(const Vector2 v) {
	printf("Vec(%.2f, %.2f)\n", v.x, v.y);
}