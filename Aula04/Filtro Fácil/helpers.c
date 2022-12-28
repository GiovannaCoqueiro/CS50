#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float escalaCinza = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //calcula a média dos tons de azul, verde e vermelho para igualá-los e resultar num tom cinza
            escalaCinza = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = escalaCinza;
            image[i][j].rgbtGreen = escalaCinza;
            image[i][j].rgbtRed = escalaCinza;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaAzul = 0, sepiaVerde = 0, sepiaVermelho = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //fórmulas para cada conversão em sépia
            sepiaAzul = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);
            sepiaVerde = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            sepiaVermelho = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);

            //não permite que ultrapasse o valor de 255 bits
            if (sepiaAzul > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaAzul;
            }

            if (sepiaVerde > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaVerde;
            }

            if (sepiaVermelho > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaVermelho;
            }
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
                    blurAzul += image[posk][posl].rgbtBlue;
                    blurVerde += image[posk][posl].rgbtGreen;
                    blurVermelho += image[posk][posl].rgbtRed;
                    contPixel++;
                }
            }

            backup[i][j].rgbtBlue = round(blurAzul / contPixel);
            backup[i][j].rgbtGreen = round(blurVerde / contPixel);
            backup[i][j].rgbtRed = round(blurVermelho / contPixel);
        }
    }

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