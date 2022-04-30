// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // create a buffer for the head
    uint8_t tmp_header[HEADER_SIZE];

    // copy header from input file to output file
    fread(tmp_header, HEADER_SIZE, 1, input);
    fwrite(tmp_header, HEADER_SIZE, 1, output);

    // create a buffer for the body
    int16_t tmp_body;

    // copy, modify and write the remaining samples
    while (fread(&tmp_body, sizeof(int16_t), 1, input))
    {
        tmp_body *= factor;
        fwrite(&tmp_body, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
