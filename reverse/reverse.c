#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3) {
        printf("Usage: ./reverse input output\n");
        return 1;
    }

    // Open input file for reading
    char *infile = argv[1];
    char *outfile = argv[2];

    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL) {
        printf("Could not open input file.\n");
        return 1;
    }

    // Read header
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, inptr);

    // Use check_format to ensure WAV format
    if (!check_format(header)) {
        printf("Input is not a wav file.\n");
        return 1;
    }
    

    // Open output file for writing
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL) {
        printf("Could not open output file.\n");
        return 1 ;
    }

    // Write header to file
    fwrite(&header, sizeof(WAVHEADER), 1, outptr);









    // Use get_block_size to calculate size of block
    int block_size = get_block_size(header);

    // Write reversed audio to file

    fseek(inptr, 0, SEEK_CUR);
    int header_end_location = ftell(inptr);
    fseek(inptr, 0, SEEK_END);
    int end_location = ftell(inptr);

    long audio_data;
    long counter = 0;

    for (long i = end_location - block_size; i >= header_end_location; i -= block_size, counter++) {
        fseek(inptr, i, SEEK_SET);

        fread(&audio_data, block_size, 1, inptr);
        fwrite(&audio_data, block_size, 1, outptr);
    }

    fclose(inptr);
    fclose(outptr);
}

int check_format(WAVHEADER header)
{   
    char file_format[20];
    strcpy(file_format, header.format);
    if (strncmp(file_format, "WAVE", 4) == 0) 
        return 1;
    
    return 0;
}

int get_block_size(WAVHEADER header)
{
    int block_size = header.numChannels * (header.bitsPerSample / 8);
    
    return block_size;
}