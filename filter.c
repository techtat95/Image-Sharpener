#include <stdlib.h>
#include <stdio.h>
#include "filter.h"

#ifndef BLUR_OFF
BMPImage * blur(BMPImage * image) {
	BoxFilter h;
	h.norm = 9;
	
	for(int z = 0; z < 3; z++){
	 for(int k = 0; k < 3; k++){
	   h.filter[z][k] = 1;
	}
       }
	return apply(image, h);
}
#endif

// EXTRA CREDIT START
BMPImage * apply(BMPImage * image, BoxFilter f) {
	BMPImage * starter = malloc(sizeof(BMPImage));

	starter -> header = image -> header;
	starter -> norm_height = image -> norm_height;

	starter -> pixels = malloc(sizeof(Pixel *) * starter -> norm_height);
	for(int i = 0; i < starter -> norm_height; ++i)
	{
	starter -> pixels[i] = malloc(sizeof(Pixel) * starter -> header.width_px);
	}
		
	int b;
	int a;
	int r;
	int g;

	for(int i = 0; i < starter -> norm_height; ++i){
	 for(int j = 0; j < starter -> header.width_px; ++j){
	 b = 0;
	 a = 0;
	 r = 0;
	 g = 0;
	for(int q = 0; q < 3; ++q){
	 for(int z = 0; z < 3; ++z){
	  if((i-1+q < 0) || (i-1+q >= starter -> norm_height) || (j-1+z < 0) || (j-1+z >= starter -> header.width_px)){
	b = b + f.filter[q][z] * image -> pixels[i][j].blue;
	a = a + f.filter[q][z] * image -> pixels[i][j].alpha;
	r = r + f.filter[q][z] * image -> pixels[i][j].red;
	g = g + f.filter[q][z] * image -> pixels[i][j].green;
	}

	else{
	b = b + f.filter[q][z] * image -> pixels[i-1+q][j-1+z].blue;
	a = a + f.filter[q][z] * image -> pixels[i-1+q][j-1+z].alpha;
	r = r + f.filter[q][z] * image -> pixels[i-1+q][j-1+z].red;
	g = g + f.filter[q][z] * image -> pixels[i-1+q][j-1+z].green;
	}		
      }
    }
	b = b / (int)f.norm;
	a = a / (int)f.norm;
	r = r / (int)f.norm;
	g = g / (int)f.norm;

	if(b > 255) 
	b = 255;
	else if
	(b<0)
	b = 0;
	starter -> pixels[i][j].blue = (uint8_t)b;

	if(a > 255)
	a = 255;
	else if
	(a<0)
	a = 0;
	starter -> pixels[i][j].alpha = (uint8_t)a;

	if(r > 255)
	r = 255;
	else if
	(r<0)
	r = 0;
	starter -> pixels[i][j].red = (uint8_t)r;
	
	if(g > 255)
	g = 255;
	else if
	(g<0)
	g = 0;
	starter -> pixels[i][j].green = (uint8_t)g;
		}
	}
	return starter;
	}
	
BoxFilter * readFilter(FILE * infile) {
	BoxFilter * newvar = malloc(sizeof(BoxFilter));
	for(int q = 0; q < 3; ++q){
	 for(int z = 0; z < 3; ++z){
		fscanf(infile, " %d", &newvar -> filter[q][z]);
	 }
	}
	fscanf(infile, "%f", &newvar -> norm);
	
	return newvar;
}
// EXTRA CREDIT END
