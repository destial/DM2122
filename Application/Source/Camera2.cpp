#include "Camera2.h"
#include "Application.h"
#include "Mtx44.h"

Camera2::Camera2() {
	fov = 45.f;
}

Camera2::~Camera2() {}

void Camera2::Init(const Vector3& pos, const Vector3& target, const Vector3& up, const float& fov) {
	this->position = pos;
	this->target = target;
	this->fov = fov;
	this->up = up;
}

void Camera2::Reset() {
	this->position = Vector3(1, 0, 1);
	this->target = Vector3(0, 0, 0);
	this->up = Vector3(0, 1, 0);
	this->fov = 45.f;
}

void Camera2::Update(double &dt, Mouse& mouse) {
	const float SENSITIVITY = 4.f * dt;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up).Normalized();
	if (mouse.left) {
		Mtx44 rotation;
		rotation.SetToRotation((float)(mouse.x_diff * SENSITIVITY), up.x, up.y, up.z);
		view = (rotation * view).Normalized();
		target = position + view;
	} else if (mouse.right) {
		Mtx44 rotation;
		rotation.SetToRotation((float)(-mouse.x_diff * SENSITIVITY), up.x, up.y, up.z);
		view = (rotation * view).Normalized();
		target = position + view;
	}
	if (mouse.up) {
		Mtx44 rotation;
		rotation.SetToRotation((float)(mouse.y_diff * SENSITIVITY), right.x, right.y, right.z);
		view = (rotation * view).Normalized();
		target = position + view;
	} else if (mouse.down) {
		Mtx44 rotation;
		rotation.SetToRotation((float)(-mouse.y_diff * SENSITIVITY), right.x, right.y, right.z);
		view = (rotation * view).Normalized();
		target = position + view;
	}

	if (position != target)
		fov += fov * mouse.scroll * SENSITIVITY;

	if (Application::IsKeyPressed('W')) {
		position += view * SENSITIVITY;
		target += view * SENSITIVITY;
	}

	if (Application::IsKeyPressed('S')) {
		position -= view * SENSITIVITY;
		target -= view * SENSITIVITY;
	}

	if (Application::IsKeyPressed('A')) {
		position -= right * SENSITIVITY;
		target -= right * SENSITIVITY;
	}

	if (Application::IsKeyPressed('D')) {
		position += right * SENSITIVITY;
		target += right * SENSITIVITY;
	}

	if (Application::IsKeyPressed(' ')) {
		position.y += SENSITIVITY;
		target.y += SENSITIVITY;
	}

	if (Application::IsKeyPressed(VK_SHIFT)) {
		position.y -= SENSITIVITY;
		target.y -= SENSITIVITY;
	}
}