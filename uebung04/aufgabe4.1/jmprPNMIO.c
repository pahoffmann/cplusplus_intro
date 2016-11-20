#include <SDL2/SDL.h>
#include <stdlib.h>
#include <string.h>
#include "jmprPNMIO.h"

enum jmpr_PNMMode mode;




void printTest(jmpr_Pixel** image,int h,int w){
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			printf("{%d, %d, %d} ",image[i][j].r,image[i][j].g,image[i][j].b);
		}
		printf("\n");
	}
}

/**
* @brief reads an image from an PNM file
*
* @param filename name of the target file
*
*/

jmpr_Image* jmpr_readImage(char* filename){
	
	/**variables
	*/

	FILE* file;
	jmpr_Image* image;
	int width;
	int height;
	char magic[2];
	char buffer[120];
	jmpr_Pixel** pixels;
	int tmp;
	unsigned char* a;
	
	/**counters
	*/
	int i;
	int j;
	
	/**trying to open the file
	*/
	file = fopen(filename, "r");
	if(NULL==file){
		fputs("error",stderr);
		return NULL;
	}
	/**getting parameters, skipping whitespace
	*/
	fscanf(file,"%s",magic);
	fgets(buffer,sizeof(buffer),file);
	printf("%s\n", buffer);
	fgets(buffer,sizeof(buffer),file);
	printf("%s\n", buffer);
	fscanf(file,"%d",&width);
	fscanf(file,"%d",&height);
	printf("%s, %d, %d\n",magic,width,height);
	fgets(buffer,sizeof(buffer),file);
	printf("%s\n", buffer);
	fgets(buffer,sizeof(buffer),file);
	printf("%s\n", buffer);

	/**allocating space for pixels array
	*/
	pixels = (jmpr_Pixel**)malloc(height* sizeof(jmpr_Pixel*));
	for(i = 0; i < height; i++){
                pixels[i] = (jmpr_Pixel*)malloc(width * sizeof(jmpr_Pixel));
        }
	
	image = (jmpr_Image*)malloc(sizeof(jmpr_Image));
	
	/**if magic number is P2
	*/
	if(!strcmp(magic,"P2")){
		mode=ASCII_PGM;
		for(i = 0; i < height ; i++){
			for(j=0;j<width;j++){
				fscanf(file,"%d",&tmp);
		  		pixels[i][j].r=(unsigned char)tmp;
				pixels[i][j].g=(unsigned char)tmp;
				pixels[i][j].b=(unsigned char)tmp;
			}
		}

	}
	/** if magic number is P3
	*/
	else if(!strcmp(magic,"P3")){
		mode = ASCII_PPM;
		for(i = 0; i < height ; i++){
			for(j=0;j<width;j++){
				fscanf(file,"%d",&tmp);
		  		pixels[i][j].r=(unsigned char)tmp;
				fscanf(file,"%d",&tmp);
				pixels[i][j].g=(unsigned char)tmp;
				fscanf(file,"%d",&tmp);
				pixels[i][j].b=(unsigned char)tmp;
			}
		}

	}
	/** if magic number is P5
	*/
	else if(!strcmp(magic,"P5")){
		mode = BINARY_PGM;
		a=(unsigned char*)malloc(width*height*sizeof(unsigned char));
		fread(a,1,width*height,file);
		for(i=0;i<height;i++){
			for(j=0;j<width;j++){
				pixels[i][j].r=a[(i*width+j)];
				pixels[i][j].g=a[(i*width+j)];
				pixels[i][j].b=a[(i*width+j)];
			}
		}

	}
	/** if magic number is P6
	*/
	else if(!strcmp(magic,"P6")){
		mode=BINARY_PPM;
		a=(unsigned char*)malloc(width*height*3*sizeof(unsigned char));
		fread(a,1,width*height*3,file);
		for(i=0;i<height;i++){
			for(j=0;j<width;j++){
				pixels[i][j].r=a[(i*width+j)*3];
				pixels[i][j].g=a[(i*width+j)*3+1];
				pixels[i][j].b=a[(i*width+j)*3+2];
			}
		}
		

	} else {
		fputs("Error",stderr);
		return NULL;
	} 
	
	image = (jmpr_Image*)malloc(sizeof(jmpr_Image));
	image->w = width;
	image->h = height;
	image->pixels = pixels;
	//printTest(pixels,height,width);
	fclose(file);
	return image;
	

	
}

/**
 * @brief Frees all resources in \ref img
 */
void jmpr_freeImage(jmpr_Image* img){
  	for(int i=0;i<img->h;i++){
		free(img->pixels[i]);
	}
	free(img->pixels);
	//free(&(img->w));
	//free(&(img->h));
   
}

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
void jmpr_savePNM(char* filename, jmpr_Image* img, enum jmpr_PNMMode mode){

  FILE* file;
  int i;
  int width = img->w;
  int height = img->h;
  int value;
  

  file = fopen(filename, "w");

  i = 255;
  
  // if mode is portable pixmap ASCII (P3)
  if(ASCII_PPM == mode){
    fprintf(file, "%s\n", "P3");
    fprintf(file, "%s\n", "# CREATOR: GIMP PNM Filter Version 1.1");
    fprintf(file, "%i %i\n%i\n", width, height, i);

    //write actual data into file
    for(int j = 0; j < height; j++){
      for(int k = 0; k < width; k++){
	fprintf(file, "%i\n", img->pixels[j][k].r);
	fprintf(file, "%i\n", img->pixels[j][k].g);
	fprintf(file, "%i\n", img->pixels[j][k].b);
      }
    }
  }

  // if mode is portable greymap ASCII (P2)
  if(ASCII_PGM == mode){
    fprintf(file, "%s\n", "P2");
    fprintf(file, "%s\n", "# CREATOR: GIMP PNM Filter Version 1.1");
    fprintf(file, "%i %i\n%i\n", width, height, i);

    //write actual data into file
    for(int j = 0; j < height; j++){
      for(int k = 0; k < width; k++){
	fprintf(file, "%i\n", ((img->pixels[j][k].r+img->pixels[j][k].g+img->pixels[j][k].b)/3));
      }
    }
  }

  
  // if mode is portable greymap binary (P5)
  if(BINARY_PGM == mode){
    fprintf(file, "%s\n", "P5");
    fprintf(file, "%s\n", "# CREATOR: GIMP PNM Filter Version 1.1");
    fprintf(file, "%i %i\n%i\n", width, height, i);

    //write actual data into file   
    for(int j = 0; j < height; j++){
      for(int k = 0; k < width; k++){
	value = (img->pixels[j][k].r+img->pixels[j][k].g+img->pixels[j][k].b)/3;
	fwrite(&value, 1, 1, file);

      }
    
    }
  

  }

   // if mode is portable pixmap binary (P6)
  if(BINARY_PPM == mode){
    fprintf(file, "%s\n", "P6");
    fprintf(file, "%s\n", "# CREATOR: GIMP PNM Filter Version 1.1");
    fprintf(file, "%i %i\n%i\n", width, height, i);

    //write actual data into file
    for(int j = 0; j < height; j++){
      for(int k = 0; k < width; k++){
	fwrite(&img->pixels[j][k].r, 1, 1, file);
	fwrite(&img->pixels[j][k].g, 1, 1, file);
	fwrite(&img->pixels[j][k].b, 1, 1, file);
      }
    
    }
  

  }

  fclose(file);
  
}

