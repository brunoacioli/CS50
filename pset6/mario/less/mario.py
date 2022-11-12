from cs50 import get_int
height = -1
while height < 1 or height > 8:
    height = get_int("Height:\n")
for i in range(height):
    for j in range(height):
        if j < height - 1 - i:
            print(" ", end="")
        else:
            print("#", end="")
    print("")    