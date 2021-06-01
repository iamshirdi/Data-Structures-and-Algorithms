// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;
typedef uint8_t BYTE8;
typedef int16_t  BYTE16;


int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files into pointer and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    
    // no memoery or invalid file
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

    // TODO: Copy header from input file to output file
    // BYTE8 header;
    // int c = 0;
    
    // while (int c < 44 )
    // {
    //     c++
    //     fwrite(&header, sizeof(BYTE8), 8 , input );
    //     printf("")
    // }
    
    // Read header first 44 bytes of each size 8- disk size, length
    BYTE8 header[44];
    fread(header, sizeof(BYTE8), 44, input);
    fwrite(&header, sizeof(BYTE8), 44, output);
    
    // Read samples
    BYTE16 buffer;
    // EOF is false while loop exists
    while (fread(&buffer, sizeof(BYTE16), 1, input))
    {
        buffer *= factor;
        fwrite(&buffer, sizeof(BYTE16), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
