#include "scene.h"
#include "scenecube.h"
#include "scenerunner.h"

int main() {
    std::unique_ptr<Scene> scene;
    SceneRunner runner("Cube Rendered");
    scene = std::unique_ptr<Scene>(new SceneCube());
    runner.run(std::move(scene));
}
