#include "scene.h"
#include "scenerunner.h"
#include "scenecube.h"

int main()
{
	std::unique_ptr<Scene> scene;
	SceneRunner runner("Cube Rendered");
	scene = std::unique_ptr<Scene>(new SceneCube());
	runner.run(std::move(scene));
}