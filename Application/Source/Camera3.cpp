#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"

Camera3::Camera3() {}

Camera3::~Camera3() {}

void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up) {
	this->position = pos;
	this->target = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up).Normalized();
	this->up = right.Cross(view).Normalized();
}

void Camera3::Reset() {}

void Camera3::Update(double &dt, Mouse& mouse) {
	const float SENSITIVITY = 4.f * dt;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up).Normalized();
	if (mouse.left) {
		Mtx44 rotation;
		rotation.SetToRotation((float)(mouse.x_diff * SENSITIVITY), up.x, up.y, up.z);
		view = (rotation * view).Normalized();
		target = position + view;
	}
	else if (mouse.right) {
		Mtx44 rotation;
		rotation.SetToRotation((float)(-mouse.x_diff * SENSITIVITY), up.x, up.y, up.z);
		view = (rotation * view).Normalized();
		target = position + view;
	}
	if (mouse.up) {
		Mtx44 rotation;
		rotation.SetToRotation((float)(-mouse.y_diff * SENSITIVITY), right.x, right.y, right.z);
		view = (rotation * view).Normalized();
		target = position + view;
	}
	else if (mouse.down) {
		Mtx44 rotation;
		rotation.SetToRotation((float)(mouse.y_diff * SENSITIVITY), right.x, right.y, right.z);
		view = (rotation * view).Normalized();
		target = position + view;
	}
	//view = (target - position).Normalized();
	//right = view.Cross(up).Normalized();
	//if (position != target)
	//	position += view * mouse.scroll * SENSITIVITY;

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
}