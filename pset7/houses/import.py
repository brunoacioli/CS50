import cs50
import csv
from sys import argv, exit


if len(argv) != 2:
    print("ERROR")
    exit(1)

with open(argv[1], "r") as file:
    reader = csv.DictReader(file)
    db = cs50.SQL("sqlite:///students.db")
    x = []
    for row in reader: 
        for j in row["name"]:
            if j == " ":
                x = row["name"].split()
        if len(x) == 2:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       x[0], None, x[1], row["house"], row["birth"])
        else:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       x[0], x[1], x[2], row["house"], row["birth"])