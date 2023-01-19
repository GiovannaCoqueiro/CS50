from cs50 import get_int
from math import floor


def main():
    n = numero_cartao()
    valid_cart(n)


# pedir o número do cartão
def numero_cartao():
    n = get_int("Insita o número do cartão: ")
    return n


# verificar validade do cartão
def valid_cart(i):
    # isola os numeros do cartão
    d1 = i % 10
    d2 = floor((i % 100) / 10)
    d3 = floor((i % 1000) / 100)
    d4 = floor((i % 10000) / 1000)
    d5 = floor((i % 100000) / 10000)
    d6 = floor((i % 1000000) / 100000)
    d7 = floor((i % 10000000) / 1000000)
    d8 = floor((i % 100000000) / 10000000)
    d9 = floor((i % 1000000000) / 100000000)
    d10 = floor((i % 10000000000) / 1000000000)
    d11 = floor((i % 100000000000) / 10000000000)
    d12 = floor((i % 1000000000000) / 100000000000)
    d13 = floor((i % 10000000000000) / 1000000000000)
    d14 = floor((i % 100000000000000) / 10000000000000)
    d15 = floor((i % 1000000000000000) / 100000000000000)
    d16 = floor((i % 10000000000000000) / 1000000000000000)

    # multiplicação das casas pré determinadas por Luhn
    n2 = d2 * 2
    n4 = d4 * 2
    n6 = d6 * 2
    n8 = d8 * 2
    n10 = d10 * 2
    n12 = d12 * 2
    n14 = d14 * 2
    n16 = d16 * 2

    # soma entre os dígitos resultantes das multiplicações e os dígitos não utilizados no cartão
    nl2 = floor((n2 / 10) + (n2 % 10))
    nl4 = floor((n4 / 10) + (n4 % 10))
    nl6 = floor((n6 / 10) + (n6 % 10))
    nl8 = floor((n8 / 10) + (n8 % 10))
    nl10 = floor((n10 / 10) + (n10 % 10))
    nl12 = floor((n12 / 10) + (n12 % 10))
    nl14 = floor((n14 / 10) + (n14 % 10))
    nl16 = floor((n16 / 10) + (n16 % 10))

    soma = nl2 + nl4 + nl6 + nl8 + nl10 + nl12 + nl14 + nl16 + d1 + d3 + d5 + d7 + d9 + d11 + d13 + d15
    result = soma % 10
    print(result)
    if result == 0:
        if (d15 == 3 and d14 == 4) or (d15 == 3 and d14 == 7):
            print("AMEX")
            return 0
        elif (d16 == 5 and d15 == 1) or (d16 == 5 and d15 == 2) or (d16 == 5 and d15 == 3) or (d16 == 5 and d15 == 4) or (d16 == 5 and d15 == 5):
            print("MASTERCARD")
            return 0
        elif (d16 == 4) or (d13 == 4 and d14 == 0 and d15 == 0 and d16 == 0):
            print("VISA")
            return 0
    else:
        print("INVALID")
        return 1


main()