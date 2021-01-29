#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"

Camera3::Camera3() {
	fov = 45.f;
}

Camera3::~Camera3() {}

void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up, const float& fov) {
	this->position = pos;
	this->target = target;
	this->fov = fov;
	this->up = up;
}

void Camera3::Reset() {
	this->position = Vector3(1, 0, 1);
	this->target = Vector3(0, 0, 0);
	this->up = Vector3(0, 1, 0);
	this->fov = 45.f;
}

void Camera3::Update(double &dt, Mouse& mouse) {
	const float SENSITIVITY = 4.f * dt;

	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(this->up).Normalized();

	if (mouse.left) {
		Mtx44 rotation;
		rotation.SetToRotation((mouse.x_diff * SENSITIVITY), this->up.x, this->up.y, this->up.z);
		view = (rotation * view).Normalized();
		target = position + view;
	} else if (mouse.right) {
		Mtx44 rotation;
		rotation.SetToRotation((-mouse.x_diff * SENSITIVITY), this->up.x, this->up.y, this->up.z);
		view = (rotation * view).Normalized();
		target = position + view;
	} 

	if (mouse.down) {
		right = view.Cross(this->up).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation((-mouse.y_diff * SENSITIVITY), right.x, right.y, right.z);
		view = (rotation * view).Normalized();
		target = position + view;
		//this->up = right.Cross(view).Normalized();
	} else if (mouse.up) {
		right = view.Cross(this->up).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation((mouse.y_diff * SENSITIVITY), right.x, right.y, right.z);
		view = (rotation * view).Normalized();
		target = position + view;
		//this->up = right.Cross(view).Normalized();
	}

	if (position != target)
		fov += fov * mouse.scroll * SENSITIVITY;

	if (Application::IsKeyPressed('W')) {
		position.x += view.x * SENSITIVITY;
		position.z += view.z * SENSITIVITY;
		target.x += view.x * SENSITIVITY;
		target.z += view.z * SENSITIVITY;
	}

	if (Application::IsKeyPressed('S')) {
		position.x -= view.x * SENSITIVITY;
		position.z -= view.z * SENSITIVITY;
		target.x -= view.x * SENSITIVITY;
		target.z -= view.z * SENSITIVITY;
	}

	if (Application::IsKeyPressed('A')) {
		position.x -= right.x * SENSITIVITY;
		position.z -= right.z * SENSITIVITY;
		target.x -= right.x * SENSITIVITY;
		target.z -= right.z * SENSITIVITY;
	}

	if (Application::IsKeyPressed('D')) {
		position.x += right.x * SENSITIVITY;
		position.z += right.z * SENSITIVITY;
		target.x += right.x * SENSITIVITY;
		target.z += right.z * SENSITIVITY;
	}

	if (Application::IsKeyPressed(' ')) {
		position.y += SENSITIVITY;
		target.y += SENSITIVITY;
	}
}