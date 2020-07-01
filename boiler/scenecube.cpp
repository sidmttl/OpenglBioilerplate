#include "scenecube.h"

#include<iostream>
using std::cerr;
using std::endl;
using glm::vec3;

SceneTriangle::SceneTriangle() {}

void SceneTriangle::initScene()
{
	compileAndLinkShader();

	glEnable(GL_DEPTH_TEST);

    view = glm::lookAt(vec3(0.0f, 0.0f, 5.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    projection = glm::mat4(1.0f);
    glm::vec4 worldLight = glm::vec4(3.0f, 5.0f, 4.0f, 1.0f);

    prog.setUniform("Light.Ld", 1.0f, 1.0f, 1.0f);
    prog.setUniform("Light.Position", view * worldLight);
    model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
}

void SceneTriangle::update(float t) {}

void SceneTriangle::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    model = glm::rotate(model, glm::radians(0.05f), glm::vec3(0.0f, 1.0f, 0.0f));
    setMatrices();

	cube.render();
}

void SceneTriangle::setMatrices()
{
    glm::mat4 mv = view * model;
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix",
        glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
    prog.setUniform("MVP", projection*mv);
}

void SceneTriangle::resize(int w, int h)
{
    glViewport(0, 0, w, h);
    width = w;
    height = h;
    projection = glm::perspective(glm::radians(70.0f), (float)w / h, 0.3f, 100.0f);
}

void SceneTriangle::compileAndLinkShader()
{
    try {
        prog.compileShader("./shaders/tri.vert.glsl");
        prog.compileShader("./shaders/tri.frag.glsl");
        //prog.compileShader("shader/function.vert.glsl");
        //prog.compileShader("shader/function.frag.glsl");
        prog.link();
        prog.use();
    }
    catch (GLSLProgramException& e) {
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}