/******************************************************************************************
    Name: Pavan T A
    Date: 16/12/24
    Title: Mp3 Tag Reader Project
    Desc: Read the Tag name and Data from .Mp3 file and Edit the tag Data of .mp3 file
******************************************************************************************/


#include "mp3.h"
 
int main(int argc, char *argv[]) 
{ 
    if (validate_Args(argc, argv) == SUCCESS) 
    { 
        if (strcmp(argv[1], "-v") == 0) 
        {
            printf("\n");
            printf("-----------------------------------------------------------------------------\n");
            printf("                         VIEW Option is Selected                             \n");
            printf("-----------------------------------------------------------------------------\n");
            FILE *file = Open_file(argv[2], "r");
            if (file) 
            {
                printf("The Data and Tag Names in Mp3 file are : \n");
                printf("\n");
                if (View_file(file) == SUCCESS) 
                {
                    printf("-----------------------------------------------------------------------------\n");
                    printf("                      Viewed MP3 File Data Successfully                      \n");
                    printf("-----------------------------------------------------------------------------\n");
                }
                else
                {
                    printf("Failed to View the MP3 File Data\n");
                    fclose(file);
                    return FAILURE;
                }
                fclose(file);
            }
            else
            {
                printf("Failed to open the MP3 File\n");
                return FAILURE;
            }
        }
        if (strcmp(argv[1], "-e") == 0)
        {
            printf("\n");
            printf("-----------------------------------------------------------------------------\n");
            printf("                         Edit Option is Selected                             \n");
            printf("-----------------------------------------------------------------------------\n");
            FILE *input_file = fopen(argv[4], "rb");
            if(input_file)
            {
                //printf("MP3 File Opened Successfully\n");
                // Give new file name 
                FILE *output_file = fopen("new.mp3", "wb");
                if(output_file)
                {
                    //printf("new.MP3 File Opened Successfully\n");
                     // Determine which tag is being edited
                    char *tag = argv[2]; 
                    char *newData = argv[3]; 

                    // Call the editTag function to modify the tag
                    if (strcmp(tag, "-t") == 0) 
                    {
                        // TIT2 -> title
                        editTag(input_file, output_file, "TIT2", newData, argv);
                    } // TPE1 --> Artist
                    else if (strcmp(tag, "-a") == 0) 
                    {
                        editTag(input_file, output_file, "TPE1", newData, argv);
                    }//TALB --> Album
                    else if (strcmp(tag, "-m") == 0) 
                    { 
                        editTag(input_file, output_file, "TALB", newData, argv);
                    }// TYER --> year
                    else if (strcmp(tag, "-y") == 0) 
                    {
                        editTag(input_file, output_file, "TYER", newData, argv);
                    }// TCON --> Composer
                    else if (strcmp(tag, "-c") == 0) 
                    {
                        editTag(input_file, output_file, "TCON", newData, argv);
                    }
                    fclose(output_file);
                    printf("-----------------------------------------------------------------------------\n");
                    printf("                   Edit Option is Completed Successfully                     \n");
                    printf("-----------------------------------------------------------------------------\n");

                    // Remove the original MP3 file
                    if (remove(argv[4]) != 0) 
                    {
                        perror("Error removing the original MP3 file\n");
                        fclose(input_file);
                        return FAILURE;
                    }

                    // Rename the new file to the original file name
                    if (rename("new.mp3", argv[4]) != 0) 
                    {
                        perror("Error renaming new.mp3 to the original file name\n");
                        fclose(input_file);
                        return FAILURE;
                    }

                }
                else
                {
                    printf("Failed to open the new.mp3 File\n");
                    fclose(input_file);
                    return FAILURE;
                }
                fclose(input_file);
            }
            else
            {
                printf("Failed to open the MP3 File\n");
                return FAILURE;
            }
        }
    }
    return 0;
}
