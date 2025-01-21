/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				HuangZheng
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	//YOUR CODE HERE
	if (row < 0 || row >= image->rows || col < 0 || col >= image->cols) {
    	fprintf(stderr, "Error: Invalid row or column index\n");
    	return NULL;
	}

	uint8_t sig = 0;
	sig = image->image[row][col].B & 1;
	Color *ret = malloc(sizeof(Color));
	if (!ret) {
		fprintf(stderr, "Error: Memory allocation failed\n");
		return NULL;
	}
	ret->R = 0; ret->G = 0; ret->B = 0;
	uint8_t colorValue = sig ? 255 : 0;
	ret->R = ret->G = ret->B = colorValue;
	return ret;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
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
			Color *newp = evaluateOnePixel(image, i, j); // old -> new
			if (newp) {
				newImage->image[i][j] = *newp;
				free(newp);
			}
        }
    }
	return newImage;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
    // 检查命令行参数
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return -1;
    }

    // 读取图像数据
    Image *image = readData(argv[1]);
    if (!image) {
        fprintf(stderr, "Error: Failed to read image from file %s\n", argv[1]);
        return -1;
    }

    // 使用隐写技术提取 LSB 并创建新图像
    Image *stegoImage = steganography(image);
    if (!stegoImage) {
        fprintf(stderr, "Error: Failed to create steganography image\n");
        freeImage(image); // 释放原始图像内存
        return -1;
    }

    // 输出新图像数据
    writeData(stegoImage);

    // 释放内存
    freeImage(image);
    freeImage(stegoImage);
    return 0;	
}
