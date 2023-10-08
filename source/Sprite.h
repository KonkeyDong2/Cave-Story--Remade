#pragma once
#include <map>

struct SDL_Renderer;
struct Vector2D;

typedef unsigned int Uint32;

class Sprite {
	public:
	Sprite(const char* targetFile);
	Sprite(const char* targetFile, const Vector2D& origin);
	Sprite(const char* targetFile, Uint32 x, Uint32 y, Uint32 w, Uint32 h); //Where (0;0) is the top left of the image.
	Sprite(const char* targetFile, Uint32 x, Uint32 y, Uint32 w, Uint32 h, const Vector2D& origin);

	~Sprite();

	void Draw(const Vector2D& position);
	void Draw(const Vector2D& position, bool flipH, bool flipV);
	static void SetBoundedRenderer(SDL_Renderer* bindingRenderer);

	private:
	Vector2D* origin; //Where (0;0) is the bottom left of the image.

	Uint32 width, height;
	Uint32 sourceX, sourceY;

	struct Texture;
	Texture* targetTexture;
	friend void CreateTexture(const char* targetFile);

	static std::map<const char*, Texture*> textureMap;

	static SDL_Renderer* boundedRenderer;
};