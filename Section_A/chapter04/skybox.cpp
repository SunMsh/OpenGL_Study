#include "skybox.h"
#include "utils.h"

void SkyBox::Init(const char* ImageDir)
{
	char temp[256];
	memset(temp, 0, 256);
	strcpy(temp, ImageDir);
	strcat(temp, "front.bmp");
	mTextures[0] = CreateTexture2DFromBMP(temp);
}

void SkyBox::Draw()
{
	/* To keep the z-buffer unchanged */
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mTextures[0]);
	glBegin(GL_QUADS);
	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glEnd();
}
