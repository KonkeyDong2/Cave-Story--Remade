#pragma once

struct Vector2D;

typedef unsigned int Uint32;

class Camera {
	public:
	static Camera* Instantiate(Uint32 width, Uint32 height); //In pixels...
	static Camera* Instantiate(Uint32 width, Uint32 height, const Vector2D& position);
	static Camera* GetCurrentInstance();
	static void Destroy();

	Camera(const Camera& coppiedObject) = delete;

	const Vector2D* GetPosition(); //Is this an acceptable way of returning the position of the camera?
	Uint32 GetWidth();
	Uint32 GetHeight();

	private:
	Camera();
	~Camera();

	Vector2D* position;
	Uint32 width, height;

	static Camera* currentInstance;
};