//Criar um programa que avalie se um cartão é legítimo, e diga se é Visa, MasterCard ou American Express
#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    //Pedir o número do cartão
    int d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16;
    int n2, n4, n6, n8, n10, n12, n14, n16;
    int nl2, nl4, nl6, nl8, nl10, nl12, nl14, nl16;
    int soma, valido = 0;
    long numero_cartao = 0;
    do
    {
        numero_cartao = get_long("Digíte o número do cartão: ");
    }
    while (valido != 0);

    //isolar os números do cartão pra primeira parte do Algoritmo de Luhn
    //d1 d2 d3 d4 d5 d6 d7 d8 d9 d10 d11 d12 d13 d14 d15 d16
    //x  x  x  x  x  x  x  x  x   x   x   x   x   x   x   x
    d1 = numero_cartao % 10;
    d2 = (numero_cartao % 100) / 10;
    d3 = (numero_cartao % 1000) /100;
    d4 = (numero_cartao % 10000) / 1000;
    d5 = (numero_cartao % 100000) / 10000;
    d6 = (numero_cartao % 1000000) / 100000;
    d7 = (numero_cartao % 10000000) / 1000000;
    d8 = (numero_cartao % 100000000) / 10000000;
    d9 = (numero_cartao % 1000000000) / 100000000;
    d10 = (numero_cartao % 10000000000) / 1000000000;
    d11 = (numero_cartao % 100000000000) / 10000000000;
    d12 = (numero_cartao % 1000000000000) / 100000000000;
    d13 = (numero_cartao % 10000000000000) / 1000000000000;
    d14 = (numero_cartao % 100000000000000) / 10000000000000;
    d15 = (numero_cartao % 1000000000000000) / 100000000000000;
    d16 = (numero_cartao % 10000000000000000) / 1000000000000000;

    //fazer a multiplicação de casas pré determinadas por 2
    n2 = ((numero_cartao % 100) / 10) * 2;
    n4 = ((numero_cartao % 10000) / 1000) * 2;
    n6 = ((numero_cartao % 1000000) / 100000) * 2;
    n8 = ((numero_cartao % 100000000) / 10000000) * 2;
    n10 = ((numero_cartao % 10000000000) / 1000000000) * 2;
    n12 = ((numero_cartao % 1000000000000) / 100000000000) * 2;
    n14 = ((numero_cartao % 100000000000000) / 10000000000000) * 2;
    n16 = ((numero_cartao % 10000000000000000) / 1000000000000000) * 2;

    //achar a soma entre os digítos resultantes das multiplicações e os digítos não utilizados no cartão
    //o cartão é valido se essa soma resultar um número com final 0
    nl2 = (n2 / 10) + (n2 % 10);
    nl4 = (n4 / 10) + (n4 % 10);
    nl6 = (n6 / 10) + (n6 % 10);
    nl8 = (n8 / 10) + (n8 % 10);
    nl10 = (n10 / 10) + (n10 % 10);
    nl12 = (n12 / 10) + (n12 % 10);
    nl14 = (n14 / 10) + (n14 % 10);
    nl16 = (n16 / 10) + (n16 % 10);

    soma = nl2 + nl4 + nl6 + nl8 + nl10 + nl12 + nl14 + nl16 + d1 + d3 + d5 + d7 + d9 + d11 + d13 + d15;
    valido = soma % 10;

    //descobrir a bandeira do cartão
    if (((d15 == 3 && d14 == 4) || (d15 == 3 && d14 == 7)) && valido == 0)
    {
        printf("AMEX\n");
    }
    else if (((d16 == 5 && d15 == 1) || (d16 == 5 && d15 == 2) || (d16 == 5 && d15 == 3) || (d16 == 5 && d15 == 4) || (d16 == 5
    && d15 == 5)) && valido == 0)
    {
        printf("MASTERCARD\n");
    }
    else if (((d16 == 4) || (d13 == 4 && numero_cartao < 5000000000000)) && valido == 0)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}