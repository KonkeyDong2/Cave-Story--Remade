#include "Camera.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Sprite.h"
#include "Vector2D.h"

//Texture Definition
struct Sprite::Texture {
	SDL_Texture* SDLTexture;
	Uint32 boundSprites;
};

void CreateTexture(const char* targetFile) {
	Sprite::textureMap[targetFile] = new Sprite::Texture();
	Sprite::textureMap[targetFile]->SDLTexture = IMG_LoadTexture(Sprite::boundedRenderer, targetFile);
	if (Sprite::textureMap[targetFile]->SDLTexture == nullptr) throw "The requested sprite file could not be found";
}


//Construction and Destruction
Sprite::Sprite(const char* targetFile) {
	if (!textureMap.contains(targetFile)) CreateTexture(targetFile);
	textureMap[targetFile]->boundSprites++;
	this->targetTexture = textureMap[targetFile];

	this->sourceX = this->sourceY = 0;

	SDL_QueryTexture(this->targetTexture->SDLTexture, nullptr, nullptr, (int*)&this->width, (int*)&this->height);

	this->origin = new Vector2D(0, 0);
}

Sprite::Sprite(const char* targetFile, const Vector2D& origin) {
	if (!textureMap.contains(targetFile)) CreateTexture(targetFile);
	textureMap[targetFile]->boundSprites++;
	this->targetTexture = textureMap[targetFile];

	this->sourceX = this->sourceY = 0;

	SDL_QueryTexture(this->targetTexture->SDLTexture, nullptr, nullptr, (int*)&this->width, (int*)&this->height);

	this->origin = new Vector2D(origin);
}

Sprite::Sprite(const char* targetFile, Uint32 x, Uint32 y, Uint32 w, Uint32 h) {
	if (!textureMap.contains(targetFile)) CreateTexture(targetFile);
	textureMap[targetFile]->boundSprites++;
	this->targetTexture = textureMap[targetFile];

	this->sourceX = x;
	this->sourceY = y;

	this->width = w;
	this->height = h;

	this->origin = new Vector2D(0, 0);
}

Sprite::Sprite(const char* targetFile, Uint32 x, Uint32 y, Uint32 w, Uint32 h, const Vector2D& origin) {
	if (!textureMap.contains(targetFile)) CreateTexture(targetFile);
	textureMap[targetFile]->boundSprites++;
	this->targetTexture = textureMap[targetFile];

	this->sourceX = x;
	this->sourceY = y;

	this->width = w;
	this->height = h;

	this->origin = new Vector2D(origin);
}

Sprite::~Sprite() {
	delete this->origin;

	this->targetTexture->boundSprites--;
	if (this->targetTexture->boundSprites == 0) {
		SDL_DestroyTexture(this->targetTexture->SDLTexture);

		std::map<const char*, Texture*>::iterator it = textureMap.begin();
		while (it != textureMap.end()) {
			if (it->second == this->targetTexture) break;
			it++;
		}

		textureMap.erase(it);
		delete this->targetTexture;
	}
}


//Renderer Access
void Sprite::Draw(const Vector2D& position) {
	SDL_Rect sourceRect, destRect;

	sourceRect.x = this->sourceX;
	sourceRect.y = this->sourceY;

	sourceRect.w = destRect.w = this->width;
	sourceRect.h = destRect.h = this->height;

	Camera* camera = Camera::GetCurrentInstance();
	Vector2D cornerPosition = (*camera->GetPosition()) - Vector2D(camera->GetWidth(), -(int)camera->GetHeight())/(Vector2D::UnitPixelEquivalent * 2);
	Vector2D relativePosition = (position - *this->origin + Vector2D(0, this->height)) - cornerPosition;

	destRect.x = relativePosition.x * Vector2D::UnitPixelEquivalent;
	destRect.y = relativePosition.y * Vector2D::UnitPixelEquivalent;

	SDL_RenderCopy(boundedRenderer, targetTexture->SDLTexture, &sourceRect, &destRect);
}

void Sprite::Draw(const Vector2D& position, bool flipH, bool flipV) {
	SDL_Rect sourceRect, destRect;

	sourceRect.x = this->sourceX;
	sourceRect.y = this->sourceY;

	sourceRect.w = destRect.w = this->width;
	sourceRect.h = destRect.h = this->height;

	Camera* camera = Camera::GetCurrentInstance();
	Vector2D cornerPosition = Vector2D(camera->GetWidth(), -camera->GetHeight())/(Vector2D::UnitPixelEquivalent * 2);
	Vector2D relativePosition = (position - *this->origin + Vector2D(0, this->height)) - cornerPosition;

	destRect.x = relativePosition.x * Vector2D::UnitPixelEquivalent;
	destRect.y = relativePosition.y * Vector2D::UnitPixelEquivalent;

	SDL_RendererFlip flip = (SDL_RendererFlip)((flipV << 1) | (flipH));

	SDL_RenderCopyEx(boundedRenderer, targetTexture->SDLTexture, &sourceRect, &destRect, 0, nullptr, flip);
}

void Sprite::SetBoundedRenderer(SDL_Renderer* bindingRenderer) {
	boundedRenderer = bindingRenderer;
}


//Statics
std::map<const char*, Sprite::Texture*> Sprite::textureMap;

SDL_Renderer* Sprite::boundedRenderer;