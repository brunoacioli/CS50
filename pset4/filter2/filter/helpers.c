#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    float gx[3][3] = { {-1 , 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
    float gy[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} };
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j<width; j++)
        {
            float redx = 0;
            float redy = 0;
            float greenx = 0;
            float greeny = 0;
            float bluex = 0;
            float bluey = 0;

            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    if (i - 1 + k < 0 || i - 1 + k > height - 1 || j - 1 + l < 0 || j - 1 + l > width - 1)
                    {
                        continue;
                    }
                    redx += tmp[i - 1 + k][j - 1 + l].rgbtRed * gx[k][l];
                    redy += tmp[i - 1 + k][j - 1 + l].rgbtRed * gy[k][l];
                    greenx += tmp[i - 1 + k][j - 1 + l].rgbtGreen * gx[k][l];
                    greeny += tmp[i - 1 + k][j - 1 + l].rgbtGreen * gy[k][l];
                    bluex += tmp[i - 1 + k][j - 1 + l].rgbtBlue * gx[k][l];
                    bluey += tmp[i - 1 + k][j - 1 + l].rgbtBlue * gy[k][l];
                }
            }
            float a = round (sqrtf (redx * redx + redy * redy));
            float b = round (sqrtf (greenx * greenx + greeny * greeny));
            float c = round (sqrtf (bluex * bluex + bluey * bluey));
            if (a > 255)
            {
                a = 255;
            }
            if (b > 255)
            {
                b = 255;
            }
            if (c > 255)
            {
                c = 255;
            }
            image[i][j].rgbtRed = a;
            image[i][j].rgbtGreen = b;
            image[i][j].rgbtBlue = c;
        }
    }
    return;
}
