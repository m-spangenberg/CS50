#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// define 8-bit unsigned integer
typedef uint8_t BYTE;

// FAT blocksize global variable
static int BLOCKSIZE = 512;

int main(int argc, char *argv[])
{
    // check for only one argument
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // check if file exists
    FILE *input_image = fopen(argv[1], "r");
    if (input_image == NULL)
    {
        fclose(input_image);
        printf("Unable to open file.\n");
        return 1;
    }

    // create a block buffer
    BYTE block_buffer[BLOCKSIZE];

    // create a filename variable and allocate memory
    char *filename = malloc(sizeof(char) * 7);

    // increment counter
    int image_counter = 0;

    // declare the output image
    FILE *output_image = NULL;

    // set writemode
    int writemode = 0;

    // read JPEGs from image file
    while (fread(&block_buffer, sizeof(BYTE), BLOCKSIZE, input_image))
    {
        // when encountering a header block, write header
        if (block_buffer[0] == 0xff && block_buffer[1] == 0xd8 && block_buffer[2] == 0xff && (block_buffer[3] & 0xf0) == 0xe0)
        {
            if (writemode == 1)
            {
                writemode = 0;
                image_counter++;
            }

            sprintf(filename, "%03i.jpg", image_counter);
            output_image = fopen(filename, "w");
            fwrite(&block_buffer, sizeof(BYTE), BLOCKSIZE, output_image);
            fclose(output_image);
            writemode = 1;

        }
        else
        {
            // append tail block to file
            if (output_image != NULL)
            {
                sprintf(filename, "%03i.jpg", image_counter);
                output_image = fopen(filename, "a");
                fwrite(&block_buffer, sizeof(BYTE), BLOCKSIZE, output_image);
                fclose(output_image);
            }
            else
            {
                continue;
            }
        }
    }
    free(filename);
    fclose(input_image);
}