//criar um programa que criptografa mensagens, usando uma chave aleatória
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc != 2) //checa se tem exatamente um argumento após o comando no terminal
    {
        printf("Use: ./substitution chave\n");
        return 1;
    }

    string chave = argv[1];
    if (strlen(chave) != 26) //checa se tem exatamente 26 caracteres na chave
    {
        printf("Sua chave deve conter 26 letras\n");
        return 1;
    }

    //checa todos os caracteres são letras
    for (int i = 0, n = strlen(chave); i < n; i++)
    {
        if (!isalpha(chave[i]))
        {
            printf("Sua chave deve conter somente letras\n");
            return 1;
        }
    }

    //checa se existem letras repetidas
    for (int i = 0, n = strlen(chave); i < n; i++)
    {
        for (int j = i + 1; j < n; j++) //compara a letra atual com o resto da chave
        {
            if (tolower(chave[i]) == tolower(chave[j]))
            {
                printf("Sua chave não deve conter letras repetidas\n");
                return 1;
            }
        }
    }

    string plain = get_string("plaintext: ");
    printf("ciphertext: ");
    //Cripitografando
    for (int i = 0, n = strlen(plain); i < n; i++)
    {
        if (isalpha(plain[i])) //apenas criptografar letras
        {
            if (isupper(plain[i]))
            {
                int l = plain[i] - 65;
                printf("%c", toupper(chave[l])); //mostrar a letra criptografada na mesma caixa que foi escrita no texto simples
            }
            else if (islower(plain[i]))
            {
                int l = plain[i] - 97;
                printf("%c", tolower(chave[l]));
            }
        }
        else
        {
            printf("%c", plain[i]);
        }
    }
    printf("\n");
    return 0;
}