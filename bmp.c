#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

#ifndef READIMAGE_OFF
BMPImage * readImage(FILE * fp) {
	BMPImage * reader = malloc(sizeof(BMPImage));
	fread(&(reader -> header), sizeof(BMPHeader), 1, fp);
	
	reader -> norm_height = abs(reader -> header.height_px);
	reader -> pixels = malloc(sizeof(Pixel*) * (reader -> norm_height));
	for(int i = 0; i < reader -> norm_height; i++)
	{
	reader -> pixels[i] = malloc(sizeof(Pixel) * reader -> header.width_px);	
	for(int j = 0; j < reader -> header.width_px; j++)
	{
	fread(&(reader->pixels[i][j]), sizeof(Pixel), 1, fp);
	}
	if(reader -> header.type != -1){
	return NULL;
	}
    }
	return reader;
	
}

void freeImage(BMPImage * image) {	
	for(int i = 0; i < image->norm_height; ++i)
	{
	free(image -> pixels[i]);
	}
	free(image -> pixels);
	free(image);
	return;
}
#endif

#ifndef WRITEIMAGE_OFF
void writeImage(BMPImage * image, FILE * fp) {
	fwrite(&image->header,sizeof(image -> header),1, fp);
	
	for(int j = 0; j < image -> norm_height; ++j){
	 for(int i = 0; i < image -> header.width_px; ++i)
	{
	fwrite(&image -> pixels[j][i], 4, 1,fp);
	}
	}
	return;
}
#endif
