#pragma pack(push, 1)

#define DETECT1 0x42
#define DETECT2 0x4D

typedef struct {
  unsigned char detector1;
  unsigned char detector2;
  unsigned int bfSize;
  short res1;
  short res2;
  unsigned int offset;
  unsigned int byte_DIB;
  unsigned int width;
  unsigned int height;
  short color_planes;
  unsigned short bits_per_pixel;
  unsigned int compression;
  unsigned int padding;
  unsigned int pixels_metre_horizontal;
  unsigned int pixels_metre_vertical;
  unsigned int colors_palette;
  unsigned int important;
} Image;

typedef struct {
  unsigned char rgbBlue;
  unsigned char rgbGreen;
  unsigned char rgbRed;
  unsigned char rgbReserved;
} RGBQUAD;

typedef struct {
    Image img;
    int *data;  
} BMP;

#pragma pack(pop)




BMP* img_open(const char * filename,const char *format);
void img_print(BMP *bmp) ;
void get_size(BMP*,int*,int*);




