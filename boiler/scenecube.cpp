#include "scenecube.h"

#include <iostream>
using glm::vec3;
using std::cerr;
using std::endl;

SceneCube::SceneCube() {}

void SceneCube::initScene() {
    compileAndLinkShader();

    glEnable(GL_DEPTH_TEST);
    glm::vec4 worldLight = glm::vec4(3.0f, 5.0f, 4.0f, 1.0f);

    prog.setUniform("Light.Ld", 1.0f, 1.0f, 1.0f);
    prog.setUniform("Light.Position", view * worldLight);
    model = glm::mat4(1.0f);
    model =
        glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
}

void SceneCube::update(float t) {}

void SceneCube::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    model =
        glm::rotate(model, glm::radians(0.05f), glm::vec3(0.0f, 1.0f, 0.0f));
    setMatrices();

    cube.render();
}

void SceneCube::setMatrices() {
    glm::mat4 mv = camera.view * model;
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix",
                    glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
    prog.setUniform("MVP", camera.projection * mv);
}

void SceneCube::resize(int w, int h) {
    glViewport(0, 0, w, h);
    width = w;
    height = h;
    projection =
        glm::perspective(glm::radians(70.0f), (float)w / h, 0.3f, 100.0f);
}

void SceneCube::compileAndLinkShader() {
    try {
        prog.compileShader("./shaders/tri.vert.glsl");
        prog.compileShader("./shaders/tri.frag.glsl");
        prog.link();
        prog.use();
    } catch (GLSLProgramException& e) {
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}

void SceneCube::keyHandle(char key) {
    float speed = 0.01;
    if (key == 'w') camera.DStride(speed);
    if (key == 's') camera.DStride(-speed);
    if (key == 'a') camera.RStride(speed);
    if (key == 'd') camera.RStride(-speed);
    if (key == ' ') camera.UStride(speed);
    if (key == 'c') camera.UStride(-speed);
}

void SceneCube::mouseHandle(float pitch, float yaw) {
    camera.mouseStride(pitch, yaw);
}
