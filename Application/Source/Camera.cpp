#include "Camera.h"
#include "Application.h"

Camera::Camera() {}

Camera::~Camera() {}

void Camera::Init(const Vector3& pos, const Vector3& target, const Vector3& up) {
	this->position = pos;
	this->target = target;
	this->up = up;
}

void Camera::Reset() {}

void Camera::Update(double &dt) {
	if (Application::IsKeyPressed('W')) {
		this->position += (10 * dt);
	}
	if (Application::IsKeyPressed('S')) {
		this->position -= (10 * dt);
	}
}