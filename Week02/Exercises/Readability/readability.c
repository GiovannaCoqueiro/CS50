//criar um programa que calcula qual a série indicada para de ser um livro
//utilizando a fómula Coleman-Liau
#include <stdio.h>
#include <ctype.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)
{
    //l = letras, p = palavras, f = frases, ml = média de palavras, mf = media de frases
    int l = 0, p = 1, f = 0;
    float ml, mf;
    string s = get_string("Texto: ");

    //contador de letras
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        //contador de letras
        if (isalpha(s[i]))
        {
            l++;
        }

        //contador de palavras
        if (isspace(s[i]))
        {
            p++;
        }

        //contador de frases
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            f++;
        }
    }

    //média de letras e frases em 100 palavras e fórmula de Coleman-Liau
    ml = (l * 100) / (float) p;
    mf = (f * 100) / (float) p;
    float cl = (0.0588 * ml) - (0.296 * mf) - 15.8;

    if (cl < 1)
    {
        printf("Before Grade 1");
    }
    else if (cl > 16)
    {
        printf("Grade 16+");
    }
    else
    {
        printf("Grade %i", (int) round(cl));
    }
    printf("\n");
}