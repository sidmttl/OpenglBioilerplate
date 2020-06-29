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

			scene->update(float(glfwGetTime()));
			scene->render();
			glfwSwapBuffers(window);

			glfwPollEvents();
			int state = glfwGetKey(window, GLFW_KEY_SPACE);
			if (state == GLFW_PRESS)
				scene->animate(!scene->animating());
		}
	}
};