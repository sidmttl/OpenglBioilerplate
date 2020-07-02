#pragma once
#include<glad/glad.h>
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using glm::vec3;
using glm::mat4;
class Camera
{
public:
	vec3 pos;
	vec3 up;
	vec3 direction;
	mat4 view;
	mat4 projection;

	Camera();
	Camera(vec3 _pos, vec3 _direction, vec3 _up);
	void RStride(float val);
	void UStride(float val);
	void DStride(float val);
	void mouseStride(float pitch,float yaw);
};