#pragma once
#include "Camera.h"
#include "Shader.h"
class Fog{
public:
	Fog(Camera*);

private:
	static Shader shader;
	Camera* camera;
};