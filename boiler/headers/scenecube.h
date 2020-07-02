#pragma once

#include "scene.h"
#include"glslprogram.h"
#include <glad/glad.h>
#include "cube.h"
#include <glm/gtc/matrix_transform.hpp>
#include"camera.h"


class SceneCube : public Scene 
{
private:
	GLSLProgram prog;
	Cube cube{ "./resources/cube.obj" };
	Camera camera;
	void setMatrices();
	void compileAndLinkShader();

public:
	SceneCube();

	void initScene();
	void update(float t);
	void render();
	void resize(int,int);
	void keyHandle(char key);
	void mouseHandle(float pitch, float yaw);
};