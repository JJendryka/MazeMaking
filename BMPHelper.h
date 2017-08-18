#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class BMPHelper {

public:

    typedef struct
    {
        char b;
        char g;
        char r;
    } RGB_data;

    static void bmp_generator(char *filename, int width, int height, unsigned char *data);

};
