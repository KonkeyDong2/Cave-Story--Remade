#pragma once

class Sprite;
struct Vector2D;

typedef unsigned int Uint32;

class Animation {
	public:
	Animation(const char** targetFiles, Uint32 frameCount, Uint32 frameRate);
	Animation(const char** targetFiles, Uint32 frameCount, Uint32 frameRate, const Vector2D& origin);
	private:
	Sprite** frames;

	Uint32 framerate, framecount;
};