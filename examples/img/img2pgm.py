import os
import sys
from PIL import Image

def img2pgm(source_path):
    if not os.path.exists(source_path):
        raise ValueError(f"file '{source_path}' not exist")

    try:
        img = Image.open(source_path)
    except Exception as e:
        print(f"\033[31mErrors occur when trying to open img file '{source_path}'\n  - Reason: \033[1m{e}\033[0m")
        return None

    pgm = img.convert('L')

    file_name, _ = os.path.splitext(source_path)
    output_path = file_name + ".pgm"

    print(f"Converting '{source_path}' -> '{output_path}'")
    pgm.save(output_path)

    return output_path


if __name__ == "__main__":
    target = sys.argv[1:]

    if not target:
        print("\033[1;31mUsage:\033[0m python png2pgm.py <file1.png> <file2.jpg> ...")
        print("       python png2pgm.py *.png")
        sys.exit(1)

    print(f"Total: {len(target)} file(s)")
    cnt = 0

    for file_path in target:
        if img2pgm(file_path):
            cnt += 1

    print("-" * 50)
    if cnt == len(target):
        print(f"finished successfully")
    else:
        print(f"Only {cnt} file(s) successfully converted, which is less than {len(target)}")
        sys.exit(1)
