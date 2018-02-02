#include <stdio.h>
#include <stdlib.h>


typedef struct {
     unsigned char red,green,blue;
} PPMPixel;

typedef struct {
     int x, y;
     PPMPixel *data;
} PPMImage;


static PPMImage *readPPM(const char *filename)
{
     char buff[16];
     PPMImage *img;
     FILE *fp;
     int rgb_comp_color;
     //open PPM file for reading
     fp = fopen(filename, "rb");
     if (!fp) {
          fprintf(stderr, "Unable to open file '%s'\n", filename);
          exit(1);
     }

     //read image format
     if (!fgets(buff, sizeof(buff), fp)) {
          perror(filename);
          exit(1);
     }

    //check the image format
    if (buff[0] != 'P' || buff[1] != '6') {
         fprintf(stderr, "Invalid image format (must be 'P6')\n");
         exit(1);
    }

    //alloc memory form image
    img = (PPMImage *)malloc(sizeof(PPMImage));
    if (!img) {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

   
    //read image size information
    if (fscanf(fp, "%d %d", &img->x, &img->y) != 2) {
         fprintf(stderr, "Invalid image size (error loading '%s')\n", filename);
         exit(1);
    }

    //read rgb component
    if (fscanf(fp, "%d", &rgb_comp_color) != 1) {
         fprintf(stderr, "Invalid rgb component (error loading '%s')\n", filename);
         exit(1);
    }

    while (fgetc(fp) != '\n') ;
    //memory allocation for pixel data
    img->data = (PPMPixel*)malloc(img->x * img->y * sizeof(PPMPixel));

    if (!img) {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

    //read pixel data from file
    if (fread(img->data, 3 * img->x, img->y, fp) != img->y) {
         fprintf(stderr, "Error loading image '%s'\n", filename);
         exit(1);
    }

    fclose(fp);
    return img;
}


void writePPM(const char *filename, PPMImage *img)
{
    FILE *fp;
    //open file for output
    fp = fopen(filename, "wb");
    if (!fp) {
         fprintf(stderr, "Unable to open file '%s'\n", filename);
         exit(1);
    }

    //write the header file
    //image format
    fprintf(fp, "P6\n");

    

    //image size
    fprintf(fp, "%d %d\n",img->x,img->y);

    // rgb component depth
    fprintf(fp, "%d\n", 255);

    // pixel data
    fwrite(img->data, 3 * img->x, img->y, fp);
    fclose(fp);
}


int coords(int i, int j, int x)
{
	return (i*x + j);
}

void freePPM(PPMImage * img){
    free(img->data);
    free(img);
}

void convolution(PPMImage* src, PPMImage* dst, int histogram[6])
{
    int r;
    

	int tmp;
	for(int j = 0; j < src->x; j++)
	{
		tmp = coords(0,j,src->x);
		dst->data[tmp] = src->data[tmp];
        r=(0.2126*dst->data[tmp].red + 0.7152*dst->data[tmp].green + 0.0722*dst->data[tmp].blue +0.5)/51;
        histogram[r]++;

		tmp = coords(src->y - 1,j,src->x);
		dst->data[tmp] = src->data[tmp];
        r=(0.2126*dst->data[tmp].red + 0.7152*dst->data[tmp].green + 0.0722*dst->data[tmp].blue +0.5)/51;
        histogram[r]++;
	}

	for(int i = 0; i < src->y; i++)
	{
		tmp = coords(i,0,src->x);
		dst->data[tmp] = src->data[tmp];
        r=(0.2126*dst->data[tmp].red + 0.7152*dst->data[tmp].green + 0.0722*dst->data[tmp].blue +0.5)/51;
        histogram[r]++;

		tmp = coords(i, src->x -1,src->x);
		dst->data[tmp] = src->data[tmp];
        r=(0.2126*dst->data[tmp].red + 0.7152*dst->data[tmp].green + 0.0722*dst->data[tmp].blue +0.5)/51;
        histogram[r]++;

    }

    
	

	int red,green,blue;


	for(int i = 1; i < src->y -1; i++)
		for(int j = 1; j < src->x -1; j++)
		{
			red = 5*(int)src->data[coords(i,j,src->x)].red - (int)src->data[coords(i-1,j,src->x)].red - (int)src->data[coords(i+1,j,src->x)].red - (int)src->data[coords(i,j-1,src->x)].red - (int)src->data[coords(i,j+1,src->x)].red;
			green = 5*(int)src->data[coords(i,j,src->x)].green - (int)src->data[coords(i-1,j,src->x)].green - (int)src->data[coords(i+1,j,src->x)].green - (int)src->data[coords(i,j-1,src->x)].green - (int)src->data[coords(i,j+1,src->x)].green;
			blue = 5*(int)src->data[coords(i,j,src->x)].blue - (int)src->data[coords(i-1,j,src->x)].blue - (int)src->data[coords(i+1,j,src->x)].blue - (int)src->data[coords(i,j-1,src->x)].blue - (int)src->data[coords(i,j+1,src->x)].blue;
			if(red>255)
				red = 255;
			if(red<0)
				red = 0;
			if(green>255)
				green = 255;
			if(green<0)
				green = 0;
			if(blue>255)
				blue = 255;
			if(blue<0)
				blue = 0;
			dst->data[coords(i,j,dst->x)].red = (unsigned char)(red);
			dst->data[coords(i,j,dst->x)].green = (unsigned char)(green);
			dst->data[coords(i,j,dst->x)].blue = (unsigned char)(blue);
            r=(0.2126*dst->data[coords(i,j,dst->x)].red + 0.7152*dst->data[coords(i,j,dst->x)].green + 0.0722*dst->data[coords(i,j,dst->x)].blue +0.5)/51;
            histogram[r]++;
		}

    FILE *fp= fopen("output.txt", "wb");
    

    for(int i=0;i<5;i++)
    {
        if(i==0 || i==1) {fprintf(fp, "%d ", histogram[i] -1);}
        else if(i==2) {fprintf(fp, "%d ", histogram[i]-2);}
        else if(i==4){
            int tmp = histogram[i] + histogram[i+1];
            fprintf(fp, "%d ", tmp);

        }
        else{fprintf(fp, "%d ", histogram[i]);}
    }
    fclose(fp);
    
}



int main(int argc, char* argv[])
{
    PPMImage* img;
    int histogram[]  = {0,0,0,0,0,0};
    img = readPPM(argv[1]);
    
    PPMImage* dst = (PPMImage *)malloc(sizeof(PPMImage));
    dst->x = img->x;
    dst->y = img->y;
    dst->data = malloc(dst->x * dst->y * sizeof(PPMPixel));

    
    convolution(img, dst, histogram);

    freePPM(img);

    writePPM("output.ppm", dst);

    
    freePPM(dst);
    return 0;
    }

