//Criar um programa que pede um número ao usuário
//e então cria uma escada com o número de degraus referente ao informado
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //verificar o tamanho da escada
    //a = degrau, l = largura, esp = espaço
    int alt;
    do
    {
        alt = get_int("Determine a altura da escada: ");
    }
    while (alt < 1 || alt > 8);

    //criar os tijolos
    for (int a = 0; a < alt; a++)
    {
        //inverter o lado da escada
        for (int esp = alt - 1; esp > a; esp--)
        {
            printf(" ");
        }
        for (int l = 0; l <= a; l++)
        {
            printf("#");
        }
        printf("\n");
    }
}