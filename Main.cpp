#include "scene.h"
#include "scenerunner.h"
#include "scenecube.h"

int main()
{
	std::unique_ptr<Scene> scene;
	SceneRunner runner("Window should open");
	scene = std::unique_ptr<Scene>(new SceneTriangle());
	runner.run(std::move(scene));
}