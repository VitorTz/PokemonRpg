from pathlib import Path
from PIL import Image
import sys


def clamp(value: int | float, lo: int | float, hi: int | float) -> int | float:
    if value < lo:
        return lo
    if value > hi:
        return hi
    return value    


def main() -> None:
    input: Path = Path(sys.argv[1])
    output: Path = Path(sys.argv[2])

    image = Image.open(input).convert("RGB")
    
    size: tuple[int, int] = (1280, 720)

    left: int = 0
    top: int = 0
    n: int = 0

    while (top < image.height):
        croped: Image.Image = image.crop((left, top, clamp(left + size[0], 0, image.width), clamp(top + size[1], 0, image.height)))
        left += size[0]
        if (left > image.width):
            left = 0
            top += size[1]
        
        croped.save(output / f"{n}.png")
        
        n+= 1

if __name__ == "__main__":
    main()