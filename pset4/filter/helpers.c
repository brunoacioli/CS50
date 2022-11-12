#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float aux=0;
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            aux=roundf((float)(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3);
            image[i][j].rgbtRed= aux;
            image[i][j].rgbtGreen= aux;
            image[i][j].rgbtBlue= aux;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            float red= round(0.393* image[i][j].rgbtRed + 0.769* image[i][j].rgbtGreen + 0.189* image[i][j].rgbtBlue);
            float green= round(0.349* image[i][j].rgbtRed + 0.686* image[i][j].rgbtGreen + 0.168* image[i][j].rgbtBlue);
            float blue= round(0.272* image[i][j].rgbtRed + 0.534* image[i][j].rgbtGreen + 0.131* image[i][j].rgbtBlue);
            if(red>255)
            {
                image[i][j].rgbtRed= 255;
            }
            else
            {
                image[i][j].rgbtRed = red;
            }
            if(green>255)
            {
                image[i][j].rgbtGreen= 255;
            }
            else
            {
                image[i][j].rgbtGreen= green;
            }
            if(blue>255)
            {
                image[i][j].rgbtBlue= 255;
            }
            else
            {
                image[i][j].rgbtBlue= blue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width/2;j++)
        {
            RGBTRIPLE aux = image[i][j];
            image[i][j] = image[i][width-j-1];
            image[i][width-j-1] = aux;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    float aux=0;
    float aux1=0;
    float aux2=0;
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            tmp[i][j]= image[i][j];
        }
    }
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            if(i==0)
            {
                if(j==0)
                {
                    aux= round((float)(tmp[i][j].rgbtRed + tmp[i][j+1].rgbtRed + tmp[i+1][j].rgbtRed +tmp[i+1][j+1].rgbtRed)/4);
                    aux1= round((float)(tmp[i][j].rgbtGreen + tmp[i][j+1].rgbtGreen + tmp[i+1][j].rgbtGreen + tmp[i+1][j+1].rgbtGreen)/4);
                    aux2= round((float)(tmp[i][j].rgbtBlue + tmp[i][j+1].rgbtBlue + tmp[i+1][j].rgbtBlue + tmp[i+1][j+1].rgbtBlue)/4);
                    image[i][j].rgbtRed= aux;
                    image[i][j].rgbtGreen= aux1;
                    image[i][j].rgbtBlue= aux2;
                }
                else if(j== width-1)
                {
                    aux= round((float)(tmp[i][j].rgbtRed + tmp[i][j-1].rgbtRed +  tmp[i+1][j].rgbtRed +  tmp[i+1][j-1].rgbtRed)/4);
                    aux1= round((float)(tmp[i][j].rgbtGreen + tmp[i][j-1].rgbtGreen + tmp[i+1][j].rgbtGreen + tmp[i+1][j-1].rgbtGreen)/4);
                    aux2= round((float)(tmp[i][j].rgbtBlue + tmp[i][j-1].rgbtBlue + tmp[i+1][j].rgbtBlue + tmp[i+1][j-1].rgbtBlue)/4);
                    image[i][j].rgbtRed= aux;
                    image[i][j].rgbtGreen= aux1;
                    image[i][j].rgbtBlue= aux2;
                }
                else
                {
                    aux= round((float)(tmp[i][j].rgbtRed + tmp[i][j-1].rgbtRed + tmp[i][j+1].rgbtRed + tmp[i+1][j].rgbtRed + tmp[i+1][j-1].rgbtRed + tmp[i+1][j+1].rgbtRed)/6);
                    aux1= round((float)(tmp[i][j].rgbtGreen + tmp[i][j-1].rgbtGreen + tmp[i][j+1].rgbtGreen + tmp[i+1][j].rgbtGreen + tmp[i+1][j-1].rgbtGreen + tmp[i+1][j+1].rgbtGreen)/6);
                    aux2= round((float)(tmp[i][j].rgbtBlue + tmp[i][j-1].rgbtBlue + tmp[i][j+1].rgbtBlue + tmp[i+1][j].rgbtBlue + tmp[i+1][j-1].rgbtBlue + tmp[i+1][j+1].rgbtBlue)/6);
                    image[i][j].rgbtRed= aux;
                    image[i][j].rgbtGreen= aux1;
                    image[i][j].rgbtBlue= aux2;
                }
            }
            else if(i==height-1)
            {
                if(j==0)
                {
                    aux= round((float)(tmp[i][j].rgbtRed + tmp[i][j+1].rgbtRed + tmp[i-1][j].rgbtRed + tmp[i-1][j+1].rgbtRed)/4);
                    aux1= round((float)(tmp[i][j].rgbtGreen + tmp[i][j+1].rgbtGreen + tmp[i-1][j].rgbtGreen + tmp[i-1][j+1].rgbtGreen)/4);
                    aux2= round((float)(tmp[i][j].rgbtBlue + tmp[i][j+1].rgbtBlue + tmp[i-1][j].rgbtBlue + tmp[i-1][j+1].rgbtBlue)/4);
                    image[i][j].rgbtRed= aux;
                    image[i][j].rgbtGreen= aux1;
                    image[i][j].rgbtBlue= aux2;
                }
                else if(j== width-1)
                {
                    aux= round((float)(tmp[i][j].rgbtRed + tmp[i][j-1].rgbtRed + tmp[i-1][j].rgbtRed + tmp[i-1][j-1].rgbtRed)/4);
                    aux1= round((float)(tmp[i][j].rgbtGreen + tmp[i][j-1].rgbtGreen + tmp[i-1][j].rgbtGreen + tmp[i-1][j-1].rgbtGreen)/4);
                    aux2= round((float)(tmp[i][j].rgbtBlue + tmp[i][j-1].rgbtBlue + tmp[i-1][j].rgbtBlue + tmp[i-1][j-1].rgbtBlue)/4);
                    image[i][j].rgbtRed= aux;
                    image[i][j].rgbtGreen= aux1;
                    image[i][j].rgbtBlue= aux2;
                }
                else
                {
                    aux= round((float)(tmp[i][j].rgbtRed + tmp[i][j-1].rgbtRed + tmp[i][j+1].rgbtRed + tmp[i-1][j].rgbtRed + tmp[i-1][j-1].rgbtRed + tmp[i-1][j+1].rgbtRed)/6);
                    aux1= round((float)(tmp[i][j].rgbtGreen + tmp[i][j-1].rgbtGreen + tmp[i][j+1].rgbtGreen + tmp[i-1][j].rgbtGreen + tmp[i-1][j-1].rgbtGreen + tmp[i-1][j+1].rgbtGreen)/6);
                    aux2= round((float)(tmp[i][j].rgbtBlue + tmp[i][j-1].rgbtBlue + tmp[i][j+1].rgbtBlue + tmp[i-1][j].rgbtBlue + tmp[i-1][j-1].rgbtBlue + tmp[i-1][j+1].rgbtBlue)/6);
                    image[i][j].rgbtRed= aux;
                    image[i][j].rgbtGreen= aux1;
                    image[i][j].rgbtBlue= aux2;
                }

            }
            else if(j== width-1)
            {
                aux= round((float)(tmp[i][j].rgbtRed + tmp[i][j-1].rgbtRed + tmp[i-1][j].rgbtRed + tmp[i-1][j-1].rgbtRed + tmp[i+1][j].rgbtRed + tmp[i+1][j-1].rgbtRed)/6);
                aux1= round((float)(tmp[i][j].rgbtGreen + tmp[i][j-1].rgbtGreen + tmp[i-1][j].rgbtGreen + tmp[i-1][j-1].rgbtGreen + tmp[i+1][j].rgbtGreen + tmp[i+1][j-1].rgbtGreen)/6);
                aux2= round((float)(tmp[i][j].rgbtBlue + tmp[i][j-1].rgbtBlue + tmp[i-1][j].rgbtBlue + tmp[i-1][j-1].rgbtBlue + tmp[i+1][j].rgbtBlue + tmp[i+1][j-1].rgbtBlue)/6);
                image[i][j].rgbtRed= aux;
                image[i][j].rgbtGreen= aux1;
                image[i][j].rgbtBlue= aux2;
            }
            else if(j== 0)
            {
                aux= round((float)(tmp[i][j].rgbtRed + tmp[i][j+1].rgbtRed + tmp[i-1][j].rgbtRed + tmp[i-1][j+1].rgbtRed + tmp[i+1][j].rgbtRed + tmp[i+1][j+1].rgbtRed)/6);
                aux1= round((float)(tmp[i][j].rgbtGreen + tmp[i][j+1].rgbtGreen + tmp[i-1][j].rgbtGreen + tmp[i-1][j+1].rgbtGreen + tmp[i+1][j].rgbtGreen + tmp[i+1][j+1].rgbtGreen)/6);
                aux2= round((float)(tmp[i][j].rgbtBlue + tmp[i][j+1].rgbtBlue + tmp[i-1][j].rgbtBlue + tmp[i-1][j+1].rgbtBlue + tmp[i+1][j].rgbtBlue + tmp[i+1][j+1].rgbtBlue)/6);
                image[i][j].rgbtRed= aux;
                image[i][j].rgbtGreen= aux1;
                image[i][j].rgbtBlue= aux2;
            }
            else
            {
                aux= round((float)(tmp[i][j].rgbtRed + tmp[i][j-1].rgbtRed + tmp[i][j+1].rgbtRed + tmp[i-1][j].rgbtRed + tmp[i-1][j-1].rgbtRed + tmp[i-1][j+1].rgbtRed + tmp[i+1][j].rgbtRed + tmp[i+1][j-1].rgbtRed + tmp[i+1][j+1].rgbtRed)/9);
                aux1= round((float)(tmp[i][j].rgbtGreen + tmp[i][j-1].rgbtGreen + tmp[i][j+1].rgbtGreen + tmp[i-1][j].rgbtGreen + tmp[i-1][j-1].rgbtGreen + tmp[i-1][j+1].rgbtGreen + tmp[i+1][j].rgbtGreen + tmp[i+1][j-1].rgbtGreen + tmp[i+1][j+1].rgbtGreen)/9);
                aux2= round((float)(tmp[i][j].rgbtBlue + tmp[i][j-1].rgbtBlue + tmp[i][j+1].rgbtBlue + tmp[i-1][j].rgbtBlue + tmp[i-1][j-1].rgbtBlue + tmp[i-1][j+1].rgbtBlue + tmp[i+1][j].rgbtBlue + tmp[i+1][j-1].rgbtBlue + tmp[i+1][j+1].rgbtBlue)/9);
                image[i][j].rgbtRed= aux;
                image[i][j].rgbtGreen= aux1;
                image[i][j].rgbtBlue= aux2;


            }
        }
    }
    return;
}