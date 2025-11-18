#include "mp3header.h"


void printusage(void)
{
    printf("--------------------------------------------------------------------------\n");
    printf("MP3 TAG READER - USAGE GUIDE                                              \n");
    printf("--------------------------------------------------------------------------\n");
    printf("./a.out -v filename.mp3                  :view Mp3 tag information        \n");
    printf("./a.out -e filename.mp3                  :edit Mp3 tag information        \n");
    printf("./a.out -h filename.mp3                  :help                            \n");
    printf("                                                                          \n");
    printf("FOR EDIT:                                                                 \n");
    printf("./a.out -e -t filename.mp3                  :Edit Mp3 Title information   \n");
    printf("./a.out -e -A filename.mp3                  :Edit Mp3 Album information   \n");
    printf("./a.out -e -a filename.mp3                  :Edit Mp3 Artist information  \n");
    printf("./a.out -e -M filename.mp3                  :Edit Mp3 Comment information \n");
    printf("./a.out -e -Y filename.mp3                  :Edit Mp3 Year information    \n");
    printf("./a.out -e -c filename.mp3                  :Edit Mp3 content information \n");
    printf("--------------------------------------------------------------------------\n");
}
int main(int argc,char *argv[])
{
    if(argc < 2)
    {
        printusage();
        return 0;
    }
     

    if (strcmp(argv[1], "-v") == 0)
    {
        if (argc < 3)
        {
            printf("Filename missing!\n");
            return 0;
        }

        int len = strlen(argv[2]);
        if (len < 4 || strcmp(argv[2] + len - 4, ".mp3") != 0)
        {
            printf("It is not a mp3 File\n");
            return 0;
        }

        viewmp3(argv[2]);
        return 0;
    }

    else if (strcmp(argv[1], "-e") == 0)
    {
        if (argc < 5)
        {
            printusage();
            return 0;
        }

        // Validate MP3 here
        int len = strlen(argv[3]);
        if (len < 4 || strcmp(argv[3] + len - 4, ".mp3") != 0)
        {
            printf("It is not a mp3 File\n");
            return 0;
        }

        edit(argv[3], argv[2], argv[4]);  
    }  
        
    

    else if(strcmp(argv[1], "-h") == 0)
    {
        printusage();    
    }
    else
    {
        printf("Use -v,-e,-h command\n");
        return 0;
    }
    return 0;
}