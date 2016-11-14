/*
 * jmprPNMIO.h
 *
 *  Created on: Nov 13, 2016
 *      Author: twiemann
 */

#ifndef JMPRPNMIO_H_
#define JMPRPNMIO_H_

typedef struct
{
	unsigned char r;   		/* Red component of a pixel   	*/
	unsigned char g;   		/* Green component of a pixel 	*/
	unsigned char b;   		/* Blue component of a pixel  	*/
}
jmpr_Pixel;

typedef struct
{
	int w;				/* Width of the image  			*/
	int h;				/* Height of the image 			*/
	jmpr_Pixel** pixels;	        /* The pixel data 		       	*/
}
jmpr_Image;

enum jmpr_PNMMode
{
	BINARY_PPM, 			/* Binary Portable Pixmap (P6) 	*/
	ASCII_PPM, 			/* Portable pixmap ASCII (P3)  	*/
	BINARY_PGM,			/* Portable Graymap binary (P5) */
	ASCII_PGM			 /* Portable Graymap ASCII (P2)	*/
};

/**
 * @brief Saves a file in binary PNM format.
 *
 * @param 	filename	The filename of the target file
 * @param	img			An jmpr_Image struct to so save
 * @param	mode		The storage mode
 *
 * If a gray map mode is selected, the image will be converted
 * into a gray scale image and color information is lost.
 */
void jmpr_savePNM(char* filename, jmpr_Image* img, enum jmpr_PNMMode mode);

/**
 * @brief Loads a jmpr_Image representation from a PNM file.
 *
 * @param	filename	A file containing PNM data
 *
 * If the given file can not be opened or contains invalid data
 * a NULL pointer will be returned. If the file contains gray
 * scale data only, the gray scale information will be stored in
 * all three channels.
 */
jmpr_Image* jmpr_readImage(char* filename);

/**
 * @brief Frees all resources in \ref img
 */
void jmpr_freeImage(jmpr_Image* img);

#endif /* JMPRPNMIO_H_ */
