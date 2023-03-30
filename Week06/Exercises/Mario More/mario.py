from cs50 import get_int


def main():
    a = get_altura()
    for i in range(a):
        # itera os espaços pra inverter a escada
        for j in range(a - 1, i, -1):
            print(" ", end="")
        # itera os blocos na escada
        for l in range(0, i + 1, 1):
            print("#", end="")
        print("  ", end="")
        # itera a segunda escada
        for k in range(0, i + 1, 1):
            print("#", end="")
        print()


# Garante a altura da escada entre 1 e 8 blocos
def get_altura():
    while True:
        n = get_int("Altura da escada: ")
        if n >= 1 and n <= 8:
            break
    return n


main()