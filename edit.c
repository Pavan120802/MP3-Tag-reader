#include "mp3.h"
 
unsigned int hexToDecimal(unsigned char hex[4]) 
{
    // Convert the 4-byte hexadecimal value to an integer
    return (hex[3] << 24) | (hex[2] << 16) | (hex[1] << 8) | hex[0];
}
 
void toLittleEndian(size_t size, unsigned char *output) 
{
    // Convert size to little-endian format
    output[0] = size & 0xFF;
    output[1] = (size >> 8) & 0xFF;
    output[2] = (size >> 16) & 0xFF;
    output[3] = (size >> 24) & 0xFF;
}

void editTag(FILE *inputFile, FILE *outputFile, const char *tag, const char *new_data, char *argv[]) 
{
    char buffer[1024];
    // initialise the count till 1024 bytes to check condition
    size_t bytes_read = fread(buffer, 1, sizeof(buffer), inputFile);
    size_t new_data_size = strlen(new_data); // Length of new data in bytes  //5 --> hello
    size_t new_size = new_data_size + 1;   //6  but store as 6
    int tagFound = 0;

    // Read the MP3 file
    while (bytes_read  > 0) 
    {
        for (size_t i = 0; i < bytes_read - 4; i++) 
        {
            // Check if the tag matches
            if (buffer[i] == tag[0] && buffer[i + 1] == tag[1] &&
                buffer[i + 2] == tag[2] && buffer[i + 3] == tag[3]) 
            {

                tagFound = 1; // tag name found

                printf("Tag to be edited: %s\n", tag);
                printf("New data to write: %s\n", new_data);

                // Write data before the tag to the new file
                fwrite(buffer, 1, i, outputFile);

                // Write the tag name (TIT2) to the new file
                fwrite(tag, 1, 4, outputFile);

                // Write the next 3 bytes (flags) to the new file
                fwrite(&buffer[i + 4], 1, 3, outputFile);

                // Read the current data size from the input file (4 bytes)
                fseek(inputFile, (i + 7), SEEK_SET);
                unsigned char current_size[4];
                fread(current_size, 1, 4, inputFile);

                // Convert current data size to integer
                unsigned int num1 = hexToDecimal(current_size);
                
                // Convert the new data size to little-endian format
                unsigned char new_data_size_bytes[4];
                toLittleEndian(new_size, new_data_size_bytes);

                // Write the new data size (4 bytes) to the output file
                fwrite(new_data_size_bytes, 1, 4, outputFile);

                // Write the new data ("hello" tag value)
                fwrite(new_data, 1, new_data_size, outputFile);

                // Skip old data in the input file
                fseek(inputFile, num1 - 1, SEEK_CUR);

                break;
            }
        }
        if (tagFound) {
            break;
        }
    }

    if (!tagFound) 
    {
        // if tag nor found
        perror("Error renaming new file to original file name");
        remove("new.mp3");
        exit(1);
    }

    // Copy remaining data from input file to output file
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), inputFile)) > 0) 
    {
        fwrite(buffer, 1, bytes_read, outputFile);
    }
}
