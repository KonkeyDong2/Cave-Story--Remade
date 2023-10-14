#pragma once
#include "Sprite.h"
#include "Vector2D.h"

Animation::Animation(const char** targetFiles, Uint32 frameCount, Uint32 frameRate) {
	this->frameCount = frameCount;
	this->frameRate = frameRate;

	this->Sprites = new Sprites*[this->frameCount];
	for (int i = 0; i < frameCount; i++) this->Sprites[i] = new Sprite(targetFiles);
}

Animation(const char** targetFiles, Uint32 frameCount, Uint32 frameRate, const Vector2D& origin);