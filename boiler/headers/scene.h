#pragma once
#include <glm/glm.hpp>

class Scene
{
protected:
	glm::mat4 model, view, projection;

public:
	int width;
	int height;

	Scene() : m_animate(true), width(800), height(600) { }
	virtual ~Scene() {}

	void setDimentions(int w, int h) {
		width = w;
		height = h;
	}

	// loading textures, initialize shaders and all
	virtual void initScene() = 0;


	//updates needed per-frame
	virtual void update(float t) = 0;

	//drawing the scene
	virtual void render() = 0;

	//resize
	virtual void resize(int, int) = 0;

	void animate(bool value) { m_animate = value; }
	bool animating() { return m_animate; }

protected:
	bool m_animate;

};