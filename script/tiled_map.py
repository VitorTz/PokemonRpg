import pygame
from pytmx.util_pygame import load_pygame
from pytmx.pytmx import TiledMap, TiledTileLayer, TiledObjectGroup, TiledObject
from enum import Enum, auto


class MapId(Enum):

    World = auto()


MAPS = {
    MapId.World: ("../src/assets/tiled-map/world.tmx", "../src/assets/tiled-map/world/map.txt")
}


def main() -> None:
    display = pygame.display.set_mode((200, 200))
    pygame.display.set_caption("TiledMap")
    map_id = MapId.World

    tiled_map: TiledMap = load_pygame(MAPS[map_id][0])
    output_file = MAPS[map_id][1]

    with open(output_file, "w+") as file:        
        file.write(f"{tiled_map.width * 16} {tiled_map.height * 16} {tiled_map.width} {tiled_map.height}\n")

        for i in tiled_map:
            if (isinstance(i, TiledObjectGroup)):
                i: TiledObjectGroup
                file.write(f"{i.name}\n")
                file.write(f"{len(i)}\n")
                for tile in i:
                    tile: TiledObject
                    file.write(f"{tile.x:.2f} {tile.y:.2f} {tile.width:.2f} {tile.height:.2f}\n")

                


if __name__ == "__main__":
    main()
