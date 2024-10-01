import pygame
from pytmx.util_pygame import load_pygame
from pytmx.pytmx import TiledMap, TiledTileLayer


def main() -> None:
    display = pygame.display.set_mode((200, 200))
    pygame.display.set_caption("TiledMap")
    tiled_map: TiledMap = load_pygame("../src/assets/tiled-map/world.tmx")
    output_file = "../src/assets/graphics/map/world/world.txt"
    
    rows = tiled_map.height
    cols = tiled_map.width
    layer: TiledTileLayer = tiled_map.get_layer_by_name("InvalidTiles")
    invalid_tiles = [x for x in layer.tiles()]
    
    with open(output_file, "w+") as file:
        file.write(f"{cols * 16} {rows * 16}\n")
        file.write(f"{rows} {cols}\n")        
        file.write(f"{len(invalid_tiles)}\n")
        for x, y, _ in invalid_tiles:
            file.write(f"{y * cols + x}\n")
    
    while True:
        for e in pygame.event.get():
            if e.type == pygame.QUIT:
                pygame.quit()
                return                
        
        display.fill((0, 0, 0))
        pygame.display.update()


if __name__ == "__main__":
    main()