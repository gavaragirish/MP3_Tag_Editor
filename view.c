#include "mp3header.h"


// Function to convert size from Big Endian to little Endian
unsigned int convert_size(unsigned char *size_bytes) 
{
    unsigned int result = 0;
    unsigned char *p = (unsigned char *)&result;

    
    p[0] = size_bytes[3];
    p[1] = size_bytes[2];
    p[2] = size_bytes[1];
    p[3] = size_bytes[0];

    return result;
}

void viewmp3(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Cannot open the mp3 file!\n");
        return;
    }
    unsigned char header[10];
    fread(header, 1, 10, fp);

    unsigned int tag_size = convert_size(&header[6]);
    unsigned int bytes_read = 0;

    while (bytes_read < tag_size) 
    {
        unsigned char tag[5] = {0};
        unsigned char size_bytes[4];
        unsigned char flags[2];

        if (fread(tag, 1, 4, fp) != 4) 
        {
        break;
        }
        if (fread(size_bytes, 1, 4, fp) != 4) 
        {
        break;
        }
        if (fread(flags, 1, 2, fp) != 2) 
        {
        break;
        }

        unsigned int size = convert_size(size_bytes);
        unsigned char *data = malloc(size);
        if (!data || fread(data, 1, size, fp) != size)
        {
            free(data);
            break;
        }

        // Skip encoding byte (first byte of data)
        char *text = (char *)(data + 1);

        if (strcmp((char *)tag, "TIT2") == 0)
        {
            printf("Title       : %s\n", text);
        }
        else if (strcmp((char *)tag, "TPE1") == 0)
        {
            printf("Artist      : %s\n", text);
        }
        else if (strcmp((char *)tag, "TALB") == 0)
        {
            printf("Album       : %s\n", text);
        }
        else if (strcmp((char *)tag, "TYER") == 0)
        {
            printf("Year        : %s\n", text);
        }
        else if (strcmp((char *)tag, "TCON") == 0)
        {
            printf("Content Type: %s\n", text);
        }
        else if (strcmp((char *)tag, "COMM") == 0)
        {
            printf("Comment    : %s\n", text);
        }

        bytes_read += 10 + size;
        free(data);
    }
}