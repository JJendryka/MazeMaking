#include <iostream>
#include "BMPHelper.h"

typedef struct tagBITMAPFILEHEADER
{
    unsigned short bfType; // 2  /* Magic identifier */
    unsigned int bfSize; // 4  /* File size in bytes */
    unsigned short bfReserved1; // 2
    unsigned short bfReserved2; // 2
    unsigned int bfOffBits; // 4 /* Offset to image data, bytes */
} __attribute__((packed)) BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
    unsigned int biSize; // 4 /* Header size in bytes */
    int biWidth; // 4 /* Width of image */
    int biHeight; // 4 /* Height of image */
    unsigned short biPlanes; // 2 /* Number of colour planes */
    unsigned short biBitCount; // 2 /* Bits per pixel */
    unsigned int biCompress; // 4 /* Compression type */
    unsigned int biSizeImage; // 4 /* Image size in bytes */
    int biXPelsPerMeter; // 4
    int biYPelsPerMeter; // 4 /* Pixels per meter */
    unsigned int biClrUsed; // 4 /* Number of colours */
    unsigned int biClrImportant; // 4 /* Important colours */
} __attribute__((packed)) BITMAPINFOHEADER;

void BMPHelper::bmp_generator(char *filename, int width, int height, unsigned char *data)
{
    BITMAPFILEHEADER bmp_head;
    BITMAPINFOHEADER bmp_info;
    int size = width * height * 3;

    bmp_head.bfType = 0x4D42; // 'BM'
    bmp_head.bfSize= size + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER); // 24 + head + info no quad
    bmp_head.bfReserved1 = bmp_head.bfReserved2 = 0;
    bmp_head.bfOffBits = bmp_head.bfSize - size;
    // finish the initial of head

    bmp_info.biSize = 40;
    bmp_info.biWidth = width;
    bmp_info.biHeight = height;
    bmp_info.biPlanes = 1;
    bmp_info.biBitCount = 24; // bit(s) per pixel, 24 is true color
    bmp_info.biCompress = 0;
    bmp_info.biSizeImage = size;
    bmp_info.biXPelsPerMeter = 0;
    bmp_info.biYPelsPerMeter = 0;
    bmp_info.biClrUsed = 0 ;
    bmp_info.biClrImportant = 0;
    // finish the initial of infohead;

    // copy the data
    FILE *fp;
    if (!(fp = fopen(filename,"wb"))) {
        std::cout<<"Failed to open a file";
        return;
    }

    fwrite(&bmp_head, 1, sizeof(BITMAPFILEHEADER), fp);
    fwrite(&bmp_info, 1, sizeof(BITMAPINFOHEADER), fp);
    fwrite(data, 1, size, fp);
    fclose(fp);
}