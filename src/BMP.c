#include "BMP.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define debug true
static Image read_(FILE *);

static Image BMP_HEADER;

Image read_(FILE *file) {

  if (file == NULL) {
    perror("[EE] File opening failed\n");
  }
  fread(&BMP_HEADER, sizeof(BMP_HEADER), 1, file);
  if (BMP_HEADER.height <= 0) {
    BMP_HEADER.height = BMP_HEADER.height * -1;
  }
  return BMP_HEADER;
}

BMP *img_open(const char *filename, const char *format) {

  FILE *file = fopen(filename, "ra");
  if (file == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

  if (strcmp(format, "BMP") != 0) {
    fprintf(stderr, "file format should be \"BMP\"\n");
    exit(EXIT_FAILURE);
  }

 
  size_t size = sizeof(FILE);
  Image img = read_(file);
  if (img.detector1 != (unsigned)DETECT1 ||
      img.detector2 != (unsigned)DETECT2) {
    fprintf(stderr, "file format is not BMP\n");
    exit(EXIT_FAILURE);
  }
  if (img.bits_per_pixel != 24 || img.compression != 0) {
    fprintf(stderr, "Image is not a 24-bit uncompressed BMP\n");
    exit(EXIT_FAILURE);
  }
#ifdef debug
  printf("detector1:%02hhX\n", img.detector1);
  printf("detector2:%c\n", img.detector2);
  printf("bfSize:%d\n", img.bfSize);
  printf("sizeof(header):%lu\n", sizeof(img));
  printf("res1:%d\n", img.res1);
  printf("res2:%d\n", img.res2);
  printf("offset:%d\n", img.offset);
  printf("byte_DIB:%d\n", img.byte_DIB);
  printf("width:%d\n", img.width);
  printf("height:%d\n", img.height);
  printf("color_planes:%d\n", img.color_planes);
  printf("bits_per_pixel:%d\n", img.bits_per_pixel);
  printf("compression:%d\n", img.compression);
  printf("padding:%d\n", img.padding);
  printf("pixels_metre_horizontal:%d\n", img.pixels_metre_horizontal);
  printf("pixels_metre_vertical:%d\n", img.pixels_metre_vertical);
  printf("colors_palette:%d\n", img.colors_palette);
  printf("important:%d\n", img.important);
#endif
  int bytesPerPixel = img.bits_per_pixel / 8;
  int rowSize = (img.width * bytesPerPixel + 3) &
                (~3); // Row size in bytes (rounded up to a multiple of 4)
  int imageSize = rowSize * img.height; // Total image size in bytes
  unsigned char *imageData = malloc(imageSize * sizeof(unsigned char));
  fread(imageData, sizeof(unsigned char), imageSize, file);
  int *data = malloc(img.width * img.height * sizeof(int));
  int dataIndex = 0;
  for (int y = img.height - 1; y >= 0; y--) {
    for (int x = 0; x < img.width; x++) {
      int byteIndex = y * rowSize + x * bytesPerPixel;
      unsigned char b = imageData[byteIndex];
      unsigned char g = imageData[byteIndex + 1];
      unsigned char r = imageData[byteIndex + 2];

      int pixelValue = (r << 16) | (g << 8) | b;
      data[dataIndex] = pixelValue;
      dataIndex++;
    }
  }
  free(imageData);
  fclose(file);

  BMP *tmp = malloc(sizeof(BMP));
  tmp->img = img;
  tmp->data = data;
  free(data);
  return tmp;
}

void img_print(BMP *bmp) {
  for (int i = 0; i < bmp->img.width; i++)
    for (int j = 0; j < bmp->img.height; j++)
      printf("data in [%d][%d] = %d \n", i, j, bmp->data[i * j]);
}

void get_size(BMP *bmp, int *width, int *height) {
  *width = bmp->img.width;
  *height = bmp->img.height;
}