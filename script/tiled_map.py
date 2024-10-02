import pygame
from pytmx.util_pygame import load_pygame
from pytmx.pytmx import TiledMap, TiledTileLayer, TiledObjectGroup, TiledObject
from enum import Enum, auto


class MapId(Enum):

    World = auto()


MAPS = {
    MapId.World: ("../src/assets/data/maps/world.tmx", "../src/assets/data/maps/world.txt")
}


def main() -> None:
    display = pygame.display.set_mode((200, 200))
    pygame.display.set_caption("TiledMap")
    map_id = MapId.World

    tiled_map: TiledMap = load_pygame(MAPS[map_id][0])
    output_file = MAPS[map_id][1]
    invalid_names = ("Objects", "Transition")
    with open(output_file, "w+") as file:
        for i in tiled_map:
            if (isinstance(i, TiledObjectGroup)) and i.name not in invalid_names:
                i: TiledObjectGroup
                file.write(f"{i.name}\n")
                file.write(f"{len(i)}\n")
                for tile in i:
                    tile: TiledObject
                    file.write(f"{tile.x:.2f} {tile.y:.2f} {tile.width:.2f} {tile.height:.2f}\n")

                


if __name__ == "__main__":
    main()
