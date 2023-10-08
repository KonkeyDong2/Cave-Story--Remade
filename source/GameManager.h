#pragma once

struct SDL_Window;
struct SDL_Renderer;

class GameManager {
	public:
	static GameManager* Instantiate();
	static GameManager* GetCurrentInstance();
	static void Destroy();

	GameManager(const GameManager& coppiedObject) = delete;

	bool IsQuitting();
	void QuitGame();

	void Initialize(const char* title, int w, int h);

	void Handle();
	void Update();
	void Render();

	void Terminate();

	private:
	GameManager();
	~GameManager();

	SDL_Window* gameWindow;
	SDL_Renderer* mainRenderer;

	bool quitting;

	static GameManager* currentInstance;
};