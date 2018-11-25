#include "scene.h"
#include "utils.h"

GLuint Texture;

void Init()
{
	glMatrixMode(GL_PROJECTION);
	gluPerspective(50.0f, 800.0f/600.0f, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	int nFileSize = 0;
	unsigned char* BmpFileContent = LoadFileContent("Res/texture.bmp", nFileSize);

	int BmpWidth = 0, BmpHeight = 0;
	unsigned char* PixelData = DecodeBMP(BmpFileContent, BmpWidth, BmpHeight);

	Texture = CreateTexture2D(PixelData, BmpWidth, BmpHeight, GL_RGB);
}

void Draw()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture);

	glBegin(GL_QUADS);
	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.1f, -0.1f, -0.4f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.1f, -0.1f, -0.4f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.1f, 0.1f, -0.4f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.1f, 0.1f, -0.4f);
	glEnd();
}
