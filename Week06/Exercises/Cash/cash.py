from cs50 import get_float


def main():
    # quarter, dime, nickel, penny
    q = 25
    d = 10
    n = 5
    p = 1
    contmoeda = 0
    valor = get_troco()
    troco = valor * 100  # converter reais pra centavos

    # utiliza as moedas das maiores para as menores
    while troco >= q:
        troco -= q
        contmoeda += 1
    while troco >= d:
        troco -= d
        contmoeda += 1
    while troco >= n:
        troco -= n
        contmoeda += 1
    while troco >= p:
        troco -= p
        contmoeda += 1
    print(contmoeda)


def get_troco():
    # garante que o valor passado seja superior a 0 reais
    while True:
        r = get_float("Valor do troco: ")
        if r > 0:
            break
    return r


main()