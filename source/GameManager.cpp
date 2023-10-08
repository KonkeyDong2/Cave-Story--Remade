#include "Camera.h"
#include "GameManager.h"
#include <SDL2/SDL.h>
#include "Sprite.h"


//Singleton Implementation
GameManager* GameManager::Instantiate() {
	if (currentInstance != nullptr) return nullptr;
	currentInstance = new GameManager();
	return currentInstance;
}

GameManager* GameManager::GetCurrentInstance() {
	return currentInstance;
}

void GameManager::Destroy() {
	delete currentInstance;
}


//Quitting Implementation
bool GameManager::IsQuitting() {
	return this->quitting;
}

void GameManager::QuitGame() {
	this->quitting = true;
}


//Game Events
void GameManager::Initialize(const char* title, int w, int h) {
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
	this->mainRenderer = SDL_CreateRenderer(this->gameWindow, -1, SDL_RENDERER_PRESENTVSYNC |  SDL_RENDERER_ACCELERATED);

	Camera::Instantiate(w, h);
	Sprite::SetBoundedRenderer(this->mainRenderer);
}

void GameManager::Handle() {
	SDL_RenderClear(this->mainRenderer);

	//TODO: Rework this
	SDL_Event currentEvent;
	while (SDL_PollEvent(&currentEvent)) {
		switch (currentEvent.type){
			case SDL_QUIT:
				this->QuitGame();
		}
	}
}
void GameManager::Update() {}
void GameManager::Render() {
	SDL_RenderPresent(this->mainRenderer);
}

void GameManager::Terminate() {
	Camera::Destroy();

	SDL_DestroyRenderer(this->mainRenderer);
	SDL_DestroyWindow(this->gameWindow);
	SDL_Quit();
}


//Construction and Destruction
GameManager::GameManager() {
	this->gameWindow = nullptr;
	this->mainRenderer = nullptr;
	this->quitting = false;
}

GameManager::~GameManager() {}


//Statics
GameManager* GameManager::currentInstance;