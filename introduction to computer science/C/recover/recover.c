#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
     return 1;
    }
    
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("cannot open");
        return 1;
    }
    // buffer of 512 bytes
    BYTE buffer[512]; 
    int count = 0;
    FILE *img_pointer = NULL;
    char filename[8];
            // reads file in chunks of 512 bytes of 8 bits repeats
        while (fread(&buffer, 512, 1, file) == 1)
        {
            // bitwise arthimetic according to brain
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                // If not first JPEG, no null point needed close previous pointer and get new pointer
                if (!(count == 0))
                {
                    fclose(img_pointer);
                }
                // Initialise file withh pointer
                sprintf(filename, "%03i.jpg", count);
                img_pointer = fopen(filename, "w");
                // counts the fiels
                count++;
            }
            // If JPEG has been found, write to file
            if (!(count == 0))
            {
                fwrite(&buffer, 512, 1, img_pointer);
            }
        }
        fclose(file);
        fclose(img_pointer);
        return 0;
    
}

