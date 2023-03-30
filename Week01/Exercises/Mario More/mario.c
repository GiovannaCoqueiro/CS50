//Criar um programa que peça um número ao usuário
//e então criar escadas espelhadas com este número
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //n = altura desejada, a = degrau, l = largura, s = espaços em branco
    int n = 0, a, l, s;
    do
    {
        n = get_int("Determine a altura da escada: ");
    }
    while (n < 1 || n > 8);

    //criar tijolos
    for (a = 0; a < n; a++)
    {
        //espelhando a primeira escada
        for (s = n - 1; s > a; s--)
        {
            printf(" ");
        }
        for (l = 0; l <= a; l++)
        {
            printf("#");
        }

        //criando a segunda escada
        printf("  ");

        for (l = 0; l <= a; l++)
        {
            printf("#");
        }
        printf("\n");
    }
}