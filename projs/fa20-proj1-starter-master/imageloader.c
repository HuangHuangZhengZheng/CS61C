/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				HuangZheng
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	//YOUR CODE HERE
	FILE *fp = fopen(filename, "r");
	if (!fp) {return NULL;}
    char format[3]; // "P3"
    if (fscanf(fp, "%2s", format) != 1 || strcmp(format, "P3") != 0) {
        fprintf(stderr, "Error: Not a valid PPM P3 file\n");
        fclose(fp);
        return NULL;
    }
    uint32_t cols, rows;
    if (fscanf(fp, "%u %u", &cols, &rows) != 2) {
        fprintf(stderr, "Error: Invalid image dimensions\n");
        fclose(fp);
        return NULL;
    }
	uint32_t maxColorValue;
    if (fscanf(fp, "%u", &maxColorValue) != 1 || maxColorValue != 255) {
        fprintf(stderr, "Error: Unsupported max color value\n");
        fclose(fp);
        return NULL;
    }
	Image *image = malloc(sizeof(Image));
    if (image == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(fp);
        return NULL;
    }
    image->rows = rows;
    image->cols = cols;	
	image->image = malloc(rows * sizeof(Color *));
    if (image->image == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        free(image);
        fclose(fp);
        return NULL;
    }

    for (uint32_t i = 0; i < rows; i++) {
        image->image[i] = malloc(cols * sizeof(Color));
        if (image->image[i] == NULL) {
            fprintf(stderr, "Error: Memory allocation failed\n");
            for (uint32_t j = 0; j < i; j++) { // have to free the former ones
                free(image->image[j]);
            }
            free(image->image);
            free(image);
            fclose(fp);
            return NULL;
        }
    }

    for (uint32_t i = 0; i < rows; i++) {
        for (uint32_t j = 0; j < cols; j++) {
            fscanf(fp, "%" SCNu8 " %" SCNu8 " %" SCNu8, // SCNu8 <=> uint8_t
                   &image->image[i][j].R,
                   &image->image[i][j].G,
                   &image->image[i][j].B);
        }
    }

    // Close the file
    fclose(fp);

    return image;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
    // Check if the image is NULL
    if (image == NULL || image->image == NULL) {
        fprintf(stderr, "Error: Invalid image data\n");
        return;
    }

    // Print the PPM header
    printf("P3\n"); // Magic number for PPM P3
    printf("%u %u\n", image->cols, image->rows); // Width and height
    printf("255\n"); // Maximum color value

    // Print pixel data
    for (uint32_t i = 0; i < image->rows; i++) {
        for (uint32_t j = 0; j < image->cols; j++) {
            printf("%3d %3d %3d", image->image[i][j].R, 
                                 image->image[i][j].G, 
                                 image->image[i][j].B);
			if (j != image->rows-1) {
				printf("   ");
			}
        }
		printf("\n");
    }
}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
    // Check if the image is NULL
    if (image == NULL) {
        return;
    }

    // Free each row of pixel data
    for (uint32_t i = 0; i < image->rows; i++) {
        free(image->image[i]);
    }

    // Free the array of row pointers
    free(image->image);

    // Free the Image structure itself
    free(image);
}