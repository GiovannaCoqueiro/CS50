//Criar um programa que calcula o crescimento de população
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int inicio, final;

    // TODO: Solicite o valor inicial ao usuário
    do
    {
        inicio = get_int("Start size: ");
    }
    while (inicio < 9);

    // TODO: Solicite o valor final ao usuário
    do
    {
        final = get_int("End size: ");
    }
    while (final < inicio);

    // TODO: Calcule o número de anos até o limite
    int anos = 0;
    while (inicio < final)
    {
        inicio = inicio + (inicio / 3) - (inicio / 4);
        anos++;
    }

    // TODO: Imprima o número de anos
    printf("Years: %i\n", anos);
}