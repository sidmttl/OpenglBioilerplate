#pragma once

#include "scene.h"
#include"glslprogram.h"
#include <glad/glad.h>
#include "cube.h"
#include <glm/gtc/matrix_transform.hpp>

class SceneTriangle : public Scene 
{
private:
	GLSLProgram prog;
	Cube cube{ "cube.obj" };

	void setMatrices();
	void compileAndLinkShader();

public:
	SceneTriangle();

	void initScene();
	void update(float t);
	void render();
	void resize(int,int);
};