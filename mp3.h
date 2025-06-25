#ifndef MP3_H
#define MP3_H
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
  
// Function declarations
int validate_Args(int argc, char *argv[]);
FILE *Open_file(const char *filename, const char *mode);
int View_file(FILE *file);
void editTag(FILE *inputFile, FILE *outputFile, const char *tagName, const char *new_data,char *argv[]);

#define SUCCESS 0
#define FAILURE 1

#endif 
