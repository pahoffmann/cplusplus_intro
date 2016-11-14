#include "jmprImageFake.h"

#include <stdlib.h>
#include <SDL2/SDL.h>

jmpr_Image* jmpr_getFakeImage()
{
	/* Width and height of the image */
	const int w = 6;
	const int h = 5;

	/* Pixel data in some manageable representation */
	const unsigned char imageData[30][3] = {
			{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 255, 255},
			{0, 255, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 255, 0}, {0, 255, 255},
			{0, 255, 0}, {0, 0, 255}, {255, 255, 255}, {0, 0, 255}, {0, 255, 0},{0, 255, 255},
			{0, 255, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 255, 0}, {0, 255, 255},
			{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 255, 255},
	};

	int i;
	int j;

	jmpr_Image* img;
	jmpr_Pixel** arr;

	/* Alloc 2D pixel array */
	arr = (jmpr_Pixel**)malloc(h * sizeof(jmpr_Pixel*));
	for(i = 0; i < h; i++)
	{
		arr[i] = (jmpr_Pixel*)malloc(w * sizeof(jmpr_Pixel));
	}

	/* Copy pixel data */
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w; j++)
		{
			arr[i][j].r = imageData[i * w + j][0];
			arr[i][j].g = imageData[i * w + j][1];
			arr[i][j].b = imageData[i * w + j][2];
		}
	}

	/* Generate image */
	img = (jmpr_Image*)malloc(sizeof(jmpr_Image));
	img->h = h;
	img->w = w;
	img->pixels = arr;

	return img;
}
