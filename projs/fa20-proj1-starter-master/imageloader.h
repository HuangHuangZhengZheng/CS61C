#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef struct Color 
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
} Color;
typedef struct Image
{
	Color **image;
	uint32_t rows;
	uint32_t cols;
} Image;

//Loads an image from a ppm file, and converts to an Image object
extern Image *readData(char *filename);

//Writes an image to stdout
extern void writeData(Image *image);

//Frees an image and all its associated data
extern void freeImage(Image *image);


// // fopen opens a file pointer to the "diary.txt" file.
// // The "r" indicates that the file should be opened in "read mode".
// // Other modes are detailed in the documentation linked above.
// FILE *fp = fopen("diary.txt", "r");

// // fscanf reads the first word and first number from the given file pointer into buf and num, 
// // respectively.
// // The second argument is a string format, specifying what exactly fscanf should be reading from the file pointer.
// // More options can for the string format can be found in the documentation linked above,
// // but you may need to Google to figure out how to scan in specific types.
// char buf[20];
// int num;
// fscanf(fp, "%s %d", buf, &num);

// // fclose simply closes the file pointer after we're done with it.
// // This frees the memory that fopen allocated for the file.
// // This is also a necessary step whenever we are writing to a file:
// // without closing the pointer, you may lose the last few lines
// // you want to write.
// fclose(fp);
