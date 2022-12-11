//criar um programa que criptografa mensagens, usando a cifra de Ceasar
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Use: ./caesar key\n");
        return 1;
    }
    else
    {
        //checa se a chave só tem números
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (!isdigit(argv[1][i]))
            {
                printf("Use: ./caesar key\n");
                return 1;
            }
        }

        int chave = (atoi(argv[1])) % 26; //converte a chave de string para int
        string plain = get_string("plaintext: ");
        printf("ciphertext: ");

        for (int i = 0, s = strlen(plain); i < s; i++)
        {
            if (isalpha(plain[i]))//criptografa letras minúsculas e maiúsculas
            {
                if ((islower(plain[i]) && ((plain[i] + chave) > 122)) || (isupper(plain[i]) && ((plain[i]) + chave) > 90))//volta ao 'a' quando chega em 'z', e pra 'A' quando chega em 'Z'
                {
                    plain[i] = plain[i] - 26;
                }
                printf("%c", plain[i] + chave);
            }
            else
            {
                printf("%c", plain[i]);
            }
        }
        printf("\n");
    }
    return 0;
}