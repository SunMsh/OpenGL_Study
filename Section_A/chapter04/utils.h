#pragma once
#include "ggl.h"

unsigned char* LoadFileContent(const char* Path, int& FileSize);
unsigned char* DecodeBMP(unsigned char* BmpFileData, int& width, int& height);
GLuint CreateTexture2D(unsigned char* PixelData, int width, int height, GLenum Type);
GLuint CreateTexture2DFromBMP(const char* BmpPath);
