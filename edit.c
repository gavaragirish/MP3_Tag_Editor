#include "mp3header.h"



// Big-endian to int 
unsigned int BE_to_int(unsigned char b[4])
{
    return (b[0] << 24) | (b[1] << 16) | (b[2] << 8) | b[3];
}

// int to big-endian 
void int_to_BE(unsigned int val, unsigned char out[4])
{
    out[0] = (val >> 24) & 0xFF;
    out[1] = (val >> 16) & 0xFF;
    out[2] = (val >> 8 ) & 0xFF;
    out[3] =  val       & 0xFF;
}

void edit(char *filename, char *option, char *new_text)
{
    char frame[5];

    // Map command-line option → Frame ID 
    if (!strcmp(option, "-t")) strcpy(frame, "TIT2");  
    else if (!strcmp(option, "-a")) strcpy(frame, "TPE1");
    else if (!strcmp(option, "-A")) strcpy(frame, "TALB");
    else if (!strcmp(option, "-M")) strcpy(frame, "COMM");
    else if (!strcmp(option, "-Y")) strcpy(frame, "TYER");
    else if (!strcmp(option, "-c")) strcpy(frame, "TCON");
    else
    {
        printf(" Invalid edit option!\n");
        return;
    }

    FILE *fp = fopen(filename, "rb");
    FILE *fp1 = fopen("temp.mp3", "wb");

    if (!fp || !fp1)
    {
        printf("File open error!\n");
        return;
    }

    unsigned char header[10];
    fread(header, 1, 10, fp);
    fwrite(header, 1, 10, fp1);

    unsigned int new_size = strlen(new_text) + 1;
    unsigned char new_BE[4];
    int_to_BE(new_size, new_BE);

    while (1)
    {
        unsigned char tag[5] = {0};
        unsigned char sz[4];
        unsigned char flags[2];

        if (fread(tag, 1, 4, fp) != 4)
            break;

        if (tag[0] == 0)
            break;

        fread(sz, 1, 4, fp);
        fread(flags, 1, 2, fp);

        unsigned int old_size = BE_to_int(sz);
        unsigned char *old_data = malloc(old_size);
        fread(old_data, 1, old_size, fp);

        if (!strcmp((char*)tag, frame))
        {
            // Write edited frame 
            fwrite(tag, 1, 4, fp1);
            fwrite(new_BE, 1, 4, fp1);
            fwrite(flags, 1, 2, fp1);

            fputc(0x00, fp1);
            fwrite(new_text, 1, strlen(new_text), fp1);

            printf("✔ Successfully updated %s\n", frame);
        }
        else
        {
            // Copy frame unchanged 
            fwrite(tag, 1, 4, fp1);
            fwrite(sz, 1, 4, fp1);
            fwrite(flags, 1, 2, fp1);
            fwrite(old_data, 1, old_size, fp1);
        }

        free(old_data);
    }

    // Copy remaining audio
    unsigned char buf[1024];
    int n;
    while ((n = fread(buf,1,1024,fp)) > 0)
        fwrite(buf,1,n,fp1);

    fclose(fp);
    fclose(fp1);

    remove(filename);
    rename("temp.mp3", filename);
}
