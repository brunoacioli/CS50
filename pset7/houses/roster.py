import cs50
from sys import argv, exit


if len(argv) != 2:
    print("Error")
    exit(1)
name = argv[1].lower()
if name not in ["slytherin", "gryffindor", "ravenclaw", "hufflepuff"]:
    print("Choose the right house")
    exit(2)
x = []
db = cs50.SQL("sqlite:///students.db")
row = db.execute("SELECT first, middle, last, birth FROM students WHERE LOWER(house) = ? ORDER BY last, first", name)
for x in row:
    a = x["first"]
    b = x["middle"]
    c = x["last"]
    d = x["birth"]
    if x["middle"] == None:
        print(f"{a} {c}, born {d}")
    else:
        print(f"{a} {b} {c}, born {d}")