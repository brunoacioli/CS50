import csv
from sys import argv, exit


def main():
    if len(argv) != 3:
        print("Needs 2 command line arguments")
        exit(1)

# Opening CSV file
    data = open(argv[1], "r")
    datareader = csv.reader(data)
    liststr = next(datareader)[1:]

# Opening txt file
    text = open(argv[2], "r")
    textreader = text.read()
    count = []
    for i in liststr:
        count.append(getmax(textreader, i))
    comparar(datareader, count)
# Closing files
    data.close()
    text.close()


def getmax(reader, strs):
    aux = [0] * len(reader)
    for i in range(len(reader) - len(strs), -1, -1):
        if reader[i:i + len(strs)] == strs:
            if i + len(strs) >= len(reader):
                aux[i] = 1
            else:
                aux[i] = aux[i + len(strs)] + 1
    return max(aux)


def comparar(lista, dados):
    for i in lista:
        name = i[0]
        valores = []
        for j in i[1:]:
            valores.append(int(j))
        if(dados == valores):
            print(name)
            return
    print("No match")


if __name__ == "__main__":
    main()