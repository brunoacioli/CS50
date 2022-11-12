#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("./Usage command\n");
        return 1;
    }
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Image could not be opened\n");
        return 2;
    }
    //typedef uint8_t BYTE;
    unsigned char *jpg = malloc(512 * sizeof(char));
    int cont = 0;
    int aux = 0;
    char image[8];
    FILE *img;
    while (fread(jpg, 512, 1, card) == 1)
    {
        if (jpg[0] == 0xff && jpg[1] == 0xd8 && jpg[2] == 0xff && (jpg[3] & 0xf0) == 0xe0)
        {
            if (aux > 0)
            {
                fclose(img);
            }
            else
            {
                aux++;
            }
            sprintf(image, "%03i.jpg", cont);
            cont ++;
            img = fopen(image, "w");
            fwrite(jpg, 512, 1, img);

        }
        else
        {
            fwrite(jpg, 512, 1, img);
        }
    }
    free(jpg);
    fclose(img);
    fclose(card);
    return 0;
}
