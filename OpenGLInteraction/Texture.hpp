//
//  Texture.hpp
//  OpenGLInteraction
//
//  Created by drinking on 11/23/15.
//  Copyright © 2015 drinking. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <stdio.h>
#include <GLUT/glut.h>
#include <iostream>
#define BITMAP_ID 0x4D42

typedef unsigned short      WORD;
typedef unsigned int       DWORD;
typedef int                LONG;

typedef struct BITMAPINFOHEADER{
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} BITMAPINFOHEADER;

typedef struct BITMAPFILEHEADER {
    WORD  bfType;
    DWORD bfSize;
    WORD  bfReserved1;
    WORD  bfReserved2;
    DWORD bfOffBits;
} BITMAPFILEHEADER;

class Texture {
private:
    unsigned char	*bitmapImage = NULL;		// bitmap图像数据
    BITMAPINFOHEADER* bitmapInfoHeader;
    int LoadBitmapFile(char *filename);
public:
    GLuint textureID;
    int LoadTexture(char* filename,GLuint textureID);
    void UseTexture();
};

#endif /* Texture_hpp */
