#include "camera.h"

Camera::Camera() : pos(vec3(0.0f,0.0f,4.0f)),
	up(vec3(0.0f,1.0f,0.0f)), 
	direction(vec3(0.0f,0.0f,-1.0f)) 
{
	view = glm::lookAt(pos, pos + direction, up);
	projection = glm::perspective(glm::radians(70.0f), (float)800 / 600, 0.3f, 100.0f);
}

Camera::Camera(vec3 _pos, vec3 _direction, vec3 _up)
{
	pos = _pos;
	direction = _direction;
	up = _up;
	view = glm::lookAt(pos, direction + pos, up);
	projection = glm::perspective(glm::radians(70.0f), (float)800 / 600, 0.3f, 100.0f);
}

void Camera::RStride(float val)
{
	pos += val* glm::cross(up, direction);;
	view = glm::lookAt(pos, pos + direction, up);
}

void Camera::DStride(float val)
{
	pos += val*direction;
	view = glm::lookAt(pos, pos + direction, up);
}

void Camera::UStride(float val)
{
	pos += val * up;
	view = glm::lookAt(pos, pos + direction, up);
}


void Camera::mouseStride(float pitch, float yaw)
{
	vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	direction = front;

	view = glm::lookAt(pos, pos+ direction, up);
}