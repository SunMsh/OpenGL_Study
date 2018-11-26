#include "utils.h"

unsigned char* DecodeBMP(unsigned char* BmpFileData, int& width, int& height)
{
	if (0x4D42 == *((unsigned short*)BmpFileData))
	{
		int PixelDataOffset = *((int*)(BmpFileData + 10));
		width = *((int*)(BmpFileData + 18));
		height = *((int*)(BmpFileData + 22));
		
		unsigned char* PixelData = BmpFileData + PixelDataOffset;
		/* the pixel format in BMP is "b g r" */
		for (int i = 0; i < width*height * 3; i += 3)
		{
			unsigned char temp = PixelData[i];
			PixelData[i] = PixelData[i + 2];
			PixelData[i + 2] = temp;
		}
		return PixelData;
	}
	else
	{
		return nullptr;
	}
}

GLuint CreateTexture2D(unsigned char* PixelData, int width, int height, GLenum Type)
{
	GLuint Texture;
	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D, Texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT/*GL_CLAMP*/);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT/*GL_CLAMP*/);
	/* Copy the texture data into GPU */
	glTexImage2D(GL_TEXTURE_2D, 0, Type, width, height, 0, Type, GL_UNSIGNED_BYTE, PixelData);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	return Texture;
}

