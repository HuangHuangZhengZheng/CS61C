/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				HuangZheng
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"


// = 0b 00 0001 100 || 0 0000 1000
//  {   lived       }{     died   }
// = 0x 1808

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	//YOUR CODE HERE
    if (!image || row < 0 || row >= image->rows || col < 0 || col >= image->cols) {
        fprintf(stderr, "Error: Invalid image or coordinates\n");
        return NULL;
    }
    // Create a new Color object
    Color *newColor = malloc(sizeof(Color));
    if (!newColor) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return NULL;
    }
    // // Initialize color values
    // newColor->R = 0;
    // newColor->G = 0;
    // newColor->B = 0;

    // Define offsets for the eight neighbors
    int offsets[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},          {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    // Count live neighbors
	int rlivedN, glivedN, blivedN;
	rlivedN = glivedN = blivedN = 0;
    for (int i = 0; i < 8; i++) {
        int neighborRow = (row + offsets[i][0] + image->rows) % image->rows; // Wrap around vertically
        int neighborCol = (col + offsets[i][1] + image->cols) % image->cols; // Wrap around horizontally

        // Assuming a live cell is represented by a non-black color (you may need to adjust this logic)
        if (image->image[neighborRow][neighborCol].R == 255) rlivedN++;
		if (image->image[neighborRow][neighborCol].G == 255) glivedN++;
		if (image->image[neighborRow][neighborCol].B == 255) blivedN++;
    }
	// find the original version of this pixel
	int rAlived, gAlived, bAlived;
	rAlived = image->image[row][col].R == 255;
	gAlived = image->image[row][col].G == 255;
	bAlived = image->image[row][col].B == 255;

	int ridx, gidx, bidx;
	ridx = 9 * rAlived + rlivedN;
	gidx = 9 * gAlived + glivedN;	
	bidx = 9 * bAlived + blivedN;
	newColor->R = (rule & (1 << ridx))? 255 : 0;
	newColor->G = (rule & (1 << gidx))? 255 : 0;
	newColor->B = (rule & (1 << bidx))? 255 : 0;
    
	return newColor;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	//YOUR CODE HERE
	if (!image) {
		fprintf(stderr, "Error: Invalid images\n");
	}
    // Create a new Image object
    Image *newImage = malloc(sizeof(Image));
    if (!newImage) {
        fprintf(stderr, "Error: Memory allocation failed for new image\n");
        return NULL;
    }

    // Set dimensions for the new image
    newImage->rows = image->rows;
    newImage->cols = image->cols;

    // Allocate memory for the pixel data of the new image
    newImage->image = malloc(newImage->rows * sizeof(Color *));
    if (!newImage->image) {
        fprintf(stderr, "Error: Memory allocation failed for pixel data\n");
        free(newImage); // Free previously allocated memory
        return NULL;
    }

    for (uint32_t i = 0; i < newImage->rows; i++) {
        newImage->image[i] = malloc(newImage->cols * sizeof(Color));
        if (!newImage->image[i]) {
            fprintf(stderr, "Error: Memory allocation failed for row %u\n", i);
            // Free previously allocated rows and the image structure
            for (uint32_t j = 0; j < i; j++) {
                free(newImage->image[j]);
            }
            free(newImage->image);
            free(newImage);
            return NULL;
        }
    }	

	for (uint32_t i = 0; i < image->rows; i++) {
        for (uint32_t j = 0; j < image->cols; j++) {
			Color *newp = evaluateOneCell(image, i, j, rule); // old -> new
			if (newp) {
				newImage->image[i][j] = *newp;
				free(newp);
			}
        }
    }
	return newImage;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <filename> <rule>\n", argv[0]);
		return -1;
	}

	// Load the image from the file
	Image *image = readData(argv[1]);
	if (!image) {
		fprintf(stderr, "Error: Failed to read image from file %s\n", argv[1]);
		return -1;
	}

	// Convert the rule from string to uint32_t
	char *endptr;
	uint32_t rule = strtol(argv[2], &endptr, 16); // Convert hex string to uint32_t
	if (*endptr != '\0') { // Check for conversion errors
		fprintf(stderr, "Error: Invalid rule format. Please provide a hexadecimal number.\n");
		freeImage(image);
		return -1;
	}

	// Compute one iteration of the Game of Life
	Image *newImage = life(image, rule);
	if (!newImage) {
		fprintf(stderr, "Error: Failed to compute next generation of Life.\n");
		freeImage(image);
		return -1;
	}

	// Output the new image data to stdout
	writeData(newImage);

	// Free allocated memory
	freeImage(image);
	freeImage(newImage);

	return 0;	

}
