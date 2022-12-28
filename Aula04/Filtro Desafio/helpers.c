#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float rgbGray = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            rgbGray = round ((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = rgbGray;
            image[i][j].rgbtGreen = rgbGray;
            image[i][j].rgbtRed = rgbGray;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE backup;
    for (int i = 0; i < height; i++)
    {
        //garante que vai inverter até a metade da imagem para não inverte-la de volta
        for (int j = 0; j < width / 2; j++)
        {
            //inverte os pixels horizontalmente na imagem
            backup = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = backup;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //copia o pixel original pra um backup
    RGBTRIPLE backup[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            backup[i][j] = image[i][j];
        }
    }

    int blurAzul, blurVerde, blurVermelho;
    float contPixel; //contador de pixels
    //looping pra verificar cada pixel
    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //zera a contagem de pixels e os valores das cores
            blurAzul = 0;
            blurVerde = 0;
            blurVermelho = 0;
            contPixel = 0.0;
            //looping pra fazer as grids de pixels
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    //posição no grid em relação ao pixel central
                    int posk = i + k;
                    int posl = j + l;

                    //não deixa ultrapassar a borda da imagem
                    if (posk < 0 || posk > (height - 1) || posl < 0 || posl > (width -1))
                    {
                        continue;
                    }
                    //atualiza o contador de pixels vizinhos e os valores de vermelho, azul e verde
                    blurAzul += image[posk][posl].rgbtBlue;
                    blurVerde += image[posk][posl].rgbtGreen;
                    blurVermelho += image[posk][posl].rgbtRed;
                    contPixel++;
                }
            }
            //calcula a média dos valores das cores da grid de pixels na matriz backup
            backup[i][j].rgbtBlue = round(blurAzul / contPixel);
            backup[i][j].rgbtGreen = round(blurVerde / contPixel);
            backup[i][j].rgbtRed = round(blurVermelho / contPixel);
        }
    }

    //devolve os valores a matriz original
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = backup[i][j].rgbtBlue;
            image[i][j].rgbtGreen = backup[i][j].rgbtGreen;
            image[i][j].rgbtRed = backup[i][j].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //copia o pixel original pra um backup
    RGBTRIPLE backup[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            backup[i][j] = image[i][j];
        }
    }

    //iniciando as matrizes horizontais e verticais
    //GX       Gy
    //-1 0 1   -1 -2 -1
    //-2 0 2    0  0  0
    //-1 0 1    1  2  1
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int bordaAzulx, bordaVerdex, bordaVermelhox, bordaAzuly, bordaVerdey, bordaVermelhoy;
    //looping pra verificar cada pixel
    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //zera os valores das cores
            bordaAzulx = 0;
            bordaVerdex = 0;
            bordaVermelhox = 0;
            bordaAzuly = 0;
            bordaVerdey = 0;
            bordaVermelhoy = 0;
            //loop para rodar nos pixels vizinhos
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    //posição nos grids em relação ao pixel central
                    int posk = i + k - 1;
                    int posl = j + l - 1;

                    //não deixa ultrapassar a borda da imagem
                    if (posk < 0 || posk > (height - 1) || posl < 0 || posl > (width -1))
                    {
                        continue;
                    }
                    bordaAzulx += image[posk][posl].rgbtBlue * Gx[k][l];
                    bordaVerdex += image[posk][posl].rgbtGreen * Gx[k][l];
                    bordaVermelhox += image[posk][posl].rgbtRed * Gx[k][l];
                    bordaAzuly += image[posk][posl].rgbtBlue * Gy[k][l];
                    bordaVerdey += image[posk][posl].rgbtGreen * Gy[k][l];
                    bordaVermelhoy += image[posk][posl].rgbtRed * Gy[k][l];
                }
            }
            //calcula o valor de vermelho, ver e azul pela formula raiz de gx^2 + gy^2
            int azul = round(sqrt(pow(bordaAzulx, 2) + pow(bordaAzuly, 2)));
            if (azul > 255)
            {
                azul = 255;
            }
            int verde = round(sqrt(pow(bordaVerdex, 2) + pow(bordaVerdey, 2)));
            if (verde > 255)
            {
                verde = 255;
            }
            int vermelho = round(sqrt(pow(bordaVermelhox, 2) + pow(bordaVermelhoy, 2)));
            if (vermelho > 255)
            {
                vermelho = 255;
            }

            backup[i][j].rgbtBlue = azul;
            backup[i][j].rgbtGreen = verde;
            backup[i][j].rgbtRed = vermelho;
        }
    }

    //devolve os valores a matriz original e garante que vão apenas até 255
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = backup[i][j].rgbtBlue;
            image[i][j].rgbtGreen = backup[i][j].rgbtGreen;
            image[i][j].rgbtRed = backup[i][j].rgbtRed;
        }
    }
    return;
}