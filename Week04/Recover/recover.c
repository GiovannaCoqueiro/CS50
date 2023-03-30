#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //não deixa continuar sem o uso correto no terminal
    if (argc != 2)
    {
        printf("Uso: ./recover file_name");
        return 1;
    }

    //pointer para o arquivo fonte
    FILE *infile = fopen(argv[1], "r"); //abre o arquivo para ler
    //não permite continuar se o arquivo for inválido
    if (infile == NULL)
    {
        printf("Arquivo inválido\n");
        return 1;
    }

    //cria os blocos de 512 bytes
    BYTE buffer[512];
    int contimagem = 0; //contador de imagens geradas
    FILE *outfile = NULL; //inicia com null, pois não tem nada escrito nele até o momento
    char *nomearq = malloc(8 * sizeof(char)); //(size_t size) aloca espaço pra chars, que ocupam 8 bits cada

    //lê o arquivo escolhido em um buffer
    //pointer pra onde deve ler, tamanho dos objetos em bytes, número de objetos, pointer de onde deve ler
    while (fread(buffer, sizeof(BYTE), 512, infile))
    {
        //verifica se existem arquivos JPEG
        //compara a operação '&' entre o quarto byte do buffer e 0xef(11110000) com 0xe0(11100000), para saber se o byte começa com 0xe
        //buffer[3] == 0xe0 || buffer[3] == 0xe1 ... buffer[3] == 0xef
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
        {
            sprintf(nomearq, "%03i.jpg", contimagem); //cria o arquivo
            outfile = fopen(nomearq, "w"); //abre o arquivo para escrever
            contimagem++;
        }

        if (outfile != NULL)
        {
            //pointer de onde deve escrever, tamanho dos objetos em bytes, número de objetos, pointer de para onde deve escrever
            fwrite(buffer, sizeof(char), 512, outfile);
        }
    }

    fclose(infile);
    fclose(outfile);
    free(nomearq);
    return 0;
}