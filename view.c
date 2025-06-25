#include "mp3.h"

FILE *Open_file(const char *filename, const char *mode) 
{
    FILE *file = fopen(filename, mode);
    if (file == NULL) 
    { 
        printf("-ERROR-\nFAILED TO OPEN FILE: %s\n", filename);
        return NULL;
    }
    return file;
} 

int View_file(FILE *file) 
{
    char buffer[5],data_size[4];
    unsigned int tag_data_size;
    // skip the 10 bytes --> header file
    fseek(file, 10, SEEK_SET);

    // loop to read tag data and tag name
    for (int i = 0; i < 7; i++) 
    {
        fread(buffer, 4, 1, file);
        buffer[4] = '\0'; 
        printf(" [%d] Tag Name: %s\n",i + 1, buffer);

        fread(data_size, 4, 1, file);
        // Convert the 4 bytes (size_c) into an integer
        tag_data_size = (data_size[0] << 21) | (data_size[1] << 14) | (data_size[2] << 7) | data_size[3];

        // skip next three bytes --> flag
        fseek(file, 3, SEEK_CUR);

        // allocate memory to store the tag data dynamically
        char *data = malloc((tag_data_size - 1) * sizeof(char));
        // to check memory allocation fails
        if(data == NULL)
        {
            printf("Memory Allocation failed\n");
            return FAILURE;
        }
        // read the tag data
        fread(data, tag_data_size - 1, 1, file);
        data[tag_data_size - 1] = '\0';
        printf("     Tag Data: %s\n",data);
        printf("\n");
        free(data);
    }
    return SUCCESS;
}




int validate_Args(int argc, char *argv[]) 
{
    // No arguments (help prompt)
    if (argc == 1) 
    {
        printf("To get help, pass --> ./a.out --help\n");
        exit(0);
    }

    // Help option
    if (argc == 2 && strcmp(argv[1], "--help") == 0) 
    {
        printf("USAGE:\n");
        printf("To view, pass --> ./a.out -v mp3_file\n");
        printf("To edit, pass --> ./a.out -e -t/-a/-A/-m/-y/-c replacement_data mp3_file\n");
        exit(0);
    }

    // View operation
    if (argc == 3 && strcmp(argv[1], "-v") == 0) 
    {
        if (strstr(argv[2], ".mp3") == NULL) 
        {
            printf("-ERROR-\nINVALID FILE FORMAT\n");
            exit(FAILURE);
        }
        //printf("Read and Validate the View Argument is Successful\n");
        return SUCCESS;
    }

    // Edit operation
    if (argc == 5 && strcmp(argv[1], "-e") == 0) 
    {
        // Validate the operation type tag
        if (!(strcmp(argv[2], "-t") == 0 || strcmp(argv[2], "-a") == 0 || strcmp(argv[2], "-A") == 0 || strcmp(argv[2], "-m") == 0 || strcmp(argv[2], "-y") == 0 || strcmp(argv[2], "-c") == 0)) 
        {
            printf("-ERROR-\nINVALID EDIT OPERATION\n");
            exit(FAILURE);
        }
        // Validate the MP3 file format
        if (strstr(argv[4], ".mp3") == NULL) 
        {
            printf("-ERROR-\nINVALID FILE FORMAT\n");
            exit(FAILURE);
        }
        //printf("Read and Validate the Edit Argument is Successful\n");
        return SUCCESS;
    }
    exit(FAILURE);
}

