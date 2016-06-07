//
//  Texture.cpp
//  OpenGLInteraction
//
//  Created by drinking on 11/23/15.
//  Copyright © 2015 drinking. All rights reserved.
//

#include "Texture.hpp"

// 纹理标示符数组，保存两个纹理的标示符
// 描述: 通过指针，返回filename 指定的bitmap文件中数据。
// 同时也返回bitmap信息头.（不支持-bit位图）
int Texture::LoadBitmapFile(char *filename)
{
    FILE *filePtr;	// 文件指针
    BITMAPFILEHEADER bitmapFileHeader;	// bitmap文件头
    int	imageIdx = 0;		// 图像位置索引
    unsigned char	tempRGB;	// 交换变量
    
    // 以“二进制+读”模式打开文件filename
    filePtr = fopen(filename, "rb");
    if (filePtr == NULL) return 0;
    // 读入bitmap文件图
    fread(&bitmapFileHeader, 14, 1, filePtr);
    
    fprintf(stderr, "file: %lu\n", sizeof(BITMAPFILEHEADER));
    fprintf(stderr, "bfType: %d\n", bitmapFileHeader.bfType);
    fprintf(stderr, "bfSize: %u\n", bitmapFileHeader.bfSize);
    fprintf(stderr, "bfReserved1: %d\n", bitmapFileHeader.bfReserved1);
    fprintf(stderr, "bfReserved2: %d\n", bitmapFileHeader.bfReserved2);
    fprintf(stderr, "bfOffBits: %u\n", bitmapFileHeader.bfOffBits);
    
    // 验证是否为bitmap文件
    if (bitmapFileHeader.bfType != BITMAP_ID) {
        fprintf(stderr, "Error in LoadBitmapFile: the file is not a bitmap file\n");
        return NULL;
    }
    
    // 读入bitmap信息头
    bitmapInfoHeader = new BITMAPINFOHEADER();
    fread(bitmapInfoHeader, 40, 1, filePtr);
    
    fprintf(stderr, "info: %lu\n", sizeof(BITMAPINFOHEADER));
    fprintf(stderr, "biSize: %u\n", bitmapInfoHeader->biSize);
    fprintf(stderr, "biWidth: %d\n", bitmapInfoHeader->biWidth);
    fprintf(stderr, "biHeight: %d\n", bitmapInfoHeader->biHeight);
    fprintf(stderr, "biPlanes: %d\n", bitmapInfoHeader->biPlanes);
    fprintf(stderr, "biBitCount: %d\n", bitmapInfoHeader->biBitCount);
    fprintf(stderr, "biCompression: %u\n", bitmapInfoHeader->biCompression);
    fprintf(stderr, "biSizeImage: %u\n", bitmapInfoHeader->biSizeImage);
    fprintf(stderr, "biXPelsPerMeter: %d\n", bitmapInfoHeader->biXPelsPerMeter);
    fprintf(stderr, "biYPelsPerMeter: %d\n", bitmapInfoHeader->biYPelsPerMeter);
    fprintf(stderr, "biClrUsed: %u\n", bitmapInfoHeader->biClrUsed);
    fprintf(stderr, "biClrImportant: %u\n", bitmapInfoHeader->biClrImportant);
    
    // 将文件指针移至bitmap数据
    fseek(filePtr, 54, SEEK_SET);
    // 为装载图像数据创建足够的内存
    bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage];
    // 验证内存是否创建成功
    if (!bitmapImage) {
        fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
        return NULL;
    }
    
    // 读入bitmap图像数据
    fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);
    // 确认读入成功
    if (bitmapImage == NULL) {
        fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
        return NULL;
    }
    
    //由于bitmap中保存的格式是BGR，下面交换R和B的值，得到RGB格式
    for (imageIdx = 0;
         imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3) {
        tempRGB = bitmapImage[imageIdx];
        bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
        bitmapImage[imageIdx + 2] = tempRGB;
    }
    // 关闭bitmap图像文件
    fclose(filePtr);
    return 1;
}

int Texture::LoadTexture(char* filename,GLuint textureID)
{
    this->textureID = textureID;
    if(LoadBitmapFile(filename)==0) return 0;
    return 1;
}

void Texture::UseTexture()
{
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    glTexImage2D(GL_TEXTURE_2D,
                 0, 	    //mipmap层次(通常为，表示最上层)
                 GL_RGB,	//我们希望该纹理有红、绿、蓝数据
                 bitmapInfoHeader->biWidth, //纹理宽带，必须是n，若有边框+2
                 bitmapInfoHeader->biHeight, //纹理高度，必须是n，若有边框+2
                 0, //边框(0=无边框, 1=有边框)
                 GL_RGB,	//bitmap数据的格式
                 GL_UNSIGNED_BYTE, //每个颜色数据的类型
                 bitmapImage);	//bitmap数据指针
}
