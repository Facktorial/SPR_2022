from random import randint

XXXX = 30
XXX = 20

def main():
    with open("output.txt", "w") as file:
        for i in range(XXX):
            file.write(" ".join([str(randint(0, XXXX)), str(randint(0, XXXX))]) + '\n') 
            file.write(" ".join([str(randint(0, XXXX)) for _ in range(randint(0,XXXX))]))
            file.write("\n")
            file.write(" ".join([str(randint(0, XXXX)) for _ in range(randint(0,XXXX))]))
            file.write("\n")
        file.write("0 0")


if __name__ == '__main__':
    main()
