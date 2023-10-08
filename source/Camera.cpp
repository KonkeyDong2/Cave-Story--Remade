#include "Camera.h"
#include "Vector2D.h"

//Singleton Implementation
Camera* Camera::Instantiate(Uint32 width, Uint32 height) {
	if (currentInstance != nullptr) return nullptr;
	currentInstance = new Camera();

	currentInstance->position = new Vector2D(0, 0);

	currentInstance->width = width;
	currentInstance->height = height;

	return currentInstance;
}

Camera* Camera::Instantiate(Uint32 width, Uint32 height, const Vector2D& position) {
	if (currentInstance != nullptr) return nullptr;
	currentInstance = new Camera();

	currentInstance->position = new Vector2D(position);

	currentInstance->width = width;
	currentInstance->height = height;

	return currentInstance;
}

Camera* Camera::GetCurrentInstance() {
	return currentInstance;
}

void Camera::Destroy() {
	delete currentInstance;
}


//Dimension Access
const Vector2D* Camera::GetPosition() {
	return this->position;
}

Uint32 Camera::GetWidth() {
	return this->width;
}

Uint32 Camera::GetHeight() {
	return this->height;
}


//Construction and Destruction
Camera::Camera() {
	this->position = nullptr;
	this->width = this->height = 0;
}

Camera::~Camera() {
	delete this->position;
}


//Statics
Camera* Camera::currentInstance;