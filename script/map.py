from pathlib import Path
import random


def main() -> None:    
    with open(Path("assets/map/world_map.txt"), "w+") as file:
        file.write("4096 4096\n")
        for i in range(4096):
            line = ''
            for j in range(4096):
                line += f"{0 if random.randint(0, 10) <= 3 else 1} "                
            file.write(line.rstrip());
            file.write('\n')


if __name__ == "__main__":
    main()