from cs50 import get_string

text = get_string("Text: ")
letras = 0
frases = 0
palavras = 1
for c in text:
    if c == ' ':
        palavras += 1
    if c in ['!', '.', '?']:
        frases += 1
    if c.isalpha() == True:
        letras += 1

L = 100 * letras / palavras
S = 100 * frases / palavras
grade = round(0.0588 * L - 0.296 * S - 15.8)
if grade >= 16:
    print("Grade 16+")
elif grade < 1:
    print("Before Grade 1")
else:
    print(f"Grade {grade}")