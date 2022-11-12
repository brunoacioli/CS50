from cs50 import get_string

op = False
while op == False:
    card = get_string("NUMBER: ")
    if card.isdigit() == True:
        op = True

if len(card) not in [13, 15, 16]:
    print("INVALID")
    exit(1)

i = len(card) - 1
produto = 0
psoma = []
count = 0
soma = 0
while i >= 0:
    if count == 1:
        produto = 2 * int(card[i])
        if produto >= 10:
            psoma.append(produto % 10)
            psoma.append(int(produto / 10))
        else:
            psoma.append(produto)
        count = 0
    else:
        soma += int(card[i])
        count = 1
    i -= 1

soma2 = sum(psoma)
stotal = soma + soma2
check = stotal % 10

if check == 0 and card[0:2] in ['51', '52', '53', '54', '55'] and len(card) == 16:
    print("MASTERCARD")
    
elif check == 0 and card[0] == '4' and len(card) in [13, 16]:
    print("VISA")
    
elif check == 0 and card[0:2] in ['34', '37'] and len(card) == 15:
    print("AMEX")

else:
    print("INVALID")
    print(card[0])