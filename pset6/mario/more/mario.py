from cs50 import get_int
height = -1
while height < 1 or height > 8:
    height = get_int("Height:\n")
for i in range(height):
    for j in range(2 * height + 2):
        if j < height - 1 - i:
            print(" ", end="")
        elif j >= height - 1 - i and j < height:
            print("#", end="")
        elif j >= height and j < height + 2:
            print(" ", end="")
        elif j > height + 1 and j < height + 3 + i:
            print("#", end="")
    print("")