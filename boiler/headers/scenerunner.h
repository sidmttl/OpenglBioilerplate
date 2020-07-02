#pragma once
#include "scene.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <memory>

bool firstMouse = 1;
float lastX = 400.0f;
float lastY = 300.0f;
float pitch = 0;
float yaw = -90.0f;

float xoffset;
float yoffset;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = 0;
	}

	xoffset = xpos - lastX;
	yoffset =  lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivtiy = 0.05f;
	xoffset *= sensitivtiy;
	yoffset *= sensitivtiy;

	yaw += xoffset;
	pitch += yoffset;
	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}
}

class SceneRunner {
private:
	GLFWwindow* window;
	int fbw, fbh;
	bool debug;
public:
	SceneRunner(const std::string& windowTitle, int width = WIN_WIDTH, int height = WIN_HEIGHT, int samples = 0) :debug(true)
	{
		if (!glfwInit()) exit(EXIT_FAILURE);

		//basically window properties
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); //for now

		if (debug)
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
		if (samples > 0) {
			glfwWindowHint(GLFW_SAMPLES, samples);
		}

		//create window
		window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, windowTitle.c_str(), NULL, NULL);
		
		if (!window) {
			std::cerr << "Unable to create OpenGL context" << std::endl;
			glfwTerminate();
			exit(EXIT_FAILURE);
		}
		
		glfwMakeContextCurrent(window);
		glfwGetFramebufferSize(window, &fbw, &fbh);
		if (!gladLoadGL()) { exit(-1); }

		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glClearColor(0.5f, 0.5f, 0.5f,1.0f);
	}

	int run(std::unique_ptr<Scene> scene)
	{
		mainLoop(window, std::move(scene));

		glfwTerminate();
		return EXIT_SUCCESS;
	}

private:

	void mainLoop(GLFWwindow* window, std::unique_ptr<Scene> scene)
	{
		scene->setDimentions(fbw, fbh);
		scene->initScene();
		scene->resize(fbw, fbh);
		while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {
			processInput(window, scene);

			scene->update(float(glfwGetTime()));
			scene->render();
			glfwSwapBuffers(window);

			glfwPollEvents();
			int state = glfwGetKey(window, GLFW_KEY_SPACE);
			if (state == GLFW_PRESS)
				scene->animate(!scene->animating());
		}
	}

	void processInput(GLFWwindow* window, std::unique_ptr<Scene>& scene)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			scene->keyHandle('w');
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			scene->keyHandle('s');
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			scene->keyHandle('a');
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			scene->keyHandle('d');
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			scene->keyHandle(' ');
		if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
			scene->keyHandle('c');
		scene->mouseHandle(pitch, yaw);
	}
};