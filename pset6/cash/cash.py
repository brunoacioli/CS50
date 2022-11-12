from cs50 import get_float
cash = -1
count = 0
while cash < 0:
    cash = get_float("Change owed:\n")
cash *= 100
if cash >= 25:
    count += int(cash / 25)
    cash = cash % 25
if cash >= 10:
    count += int(cash / 10)
    cash = cash % 10
if cash >= 5:
    count += int(cash / 5)
    cash = cash % 5
if cash > 0:
    count += cash
print(f"{count}")