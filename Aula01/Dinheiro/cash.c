// Criar um programa que dê o troco no menor número de moedas possível
#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    //q = quarter, d = dime, n = nickel, p = penny
    float real = 0;
    int q = 25, d = 10, n = 5, p = 1;

    //apenas valores positivos
    do
    {
        real = get_float("Valor do troco: ");
    }
    while (real <= 0);

    //converter de reais para centavos
    int cent = round(real * 100);

    //contar as moedas, cont = contador
    int cont = 0;
    while (cent >= q)
    {
        cent = cent - q;
        cont++;
    }
    while (cent >= d)
    {
        cent = cent - d;
        cont++;
    }
    while (cent >= n)
    {
        cent = cent - n;
        cont++;
    }
    while (cent >= p)
    {
        cent = cent - p;
        cont++;
    }

    printf("%i\n", cont);
}