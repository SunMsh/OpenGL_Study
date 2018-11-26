#include "utils.h"

unsigned char* LoadFileContent(const char* Path, int& FileSize)
{
	unsigned char* FileContent = nullptr;
	FileSize = 0;

	FILE* pFile = fopen(Path, "rb");
	if (pFile)
	{
		fseek(pFile, 0, SEEK_END);
		int nLen = ftell(pFile);
		if (nLen > 0)
		{
			rewind(pFile);
			FileContent = new unsigned char[nLen + 1];
			fread(FileContent, sizeof(unsigned char), nLen, pFile);
			FileContent[nLen] = '\0';
			FileSize = nLen;
		}
		fclose(pFile);
	}
	return FileContent;
}

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

GLuint CreateTexture2DFromBMP(const char* BmpPath)
{
	int nFileSize = 0;
	unsigned char* BmpFileContent = LoadFileContent(BmpPath, nFileSize);
	if (BmpFileContent == nullptr)
	{
		return 0;
	}

	int BmpWidth = 0, BmpHeight = 0;
	unsigned char* PixelData = DecodeBMP(BmpFileContent, BmpWidth, BmpHeight);
	if (PixelData == 0)
	{
		return 0;
	}

	GLuint Texture = CreateTexture2D(PixelData, BmpWidth, BmpHeight, GL_RGB);
	return Texture;
}
