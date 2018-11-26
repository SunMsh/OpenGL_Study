#pragma once
#include "ggl.h"

class SkyBox
{
	GLuint mTextures[6];
public:
	void Init(const char* ImageDir);
	void Draw();
};
