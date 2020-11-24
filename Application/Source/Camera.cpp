#include "Camera.h"
#include "Application.h"
#include "Mtx44.h"

Camera::Camera() {}

Camera::~Camera() {}

void Camera::Init(const Vector3& pos, const Vector3& target, const Vector3& up) {
	this->position = pos;
	this->target = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up).Normalized();
	this->up = right.Cross(view).Normalized();
}

void Camera::Reset() {}

void Camera::Update(double &dt) {
	static const float SPEED = 30.f;
	if (Application::IsKeyPressed('D')) {
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up).Normalized();
		Mtx44 rotation; rotation.SetToRotation(-(SPEED * dt), 0, 1, 0);
		position = rotation * position;
		up = rotation * up;
	}
	if (Application::IsKeyPressed('A')) {
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up).Normalized();
		Mtx44 rotation; rotation.SetToRotation((SPEED * dt), 0, 1, 0);
		position = rotation * position;
		up = rotation * up;
	}
	if (Application::IsKeyPressed('S')) {
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up).Normalized();
		Mtx44 rotation; rotation.SetToRotation((SPEED * dt), right.x, right.y, right.z);
		position = rotation * position;
		up = right.Cross(view).Normalized();
	}
	if (Application::IsKeyPressed('W')) {
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up).Normalized();
		Mtx44 rotation; rotation.SetToRotation(-(SPEED * dt), right.x, right.y, right.z);
		position = rotation * position;
		up = right.Cross(view).Normalized();
	}
	if (Application::IsKeyPressed('M')) {
		Vector3 view = (target - position).Normalized();
		position += view * SPEED * dt;
	}
	if (Application::IsKeyPressed('N')) {
		Vector3 view = (target - position).Normalized();
		position -= view * SPEED * dt;
	}
}