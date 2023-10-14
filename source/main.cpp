#include "GameManager.h"
#include "Sprite.h"
#include "Vector2D.h"

int main(int argc, char* argv[]) {
	GameManager* gameManager = GameManager::Instantiate();

	gameManager->Initialize("Cave Story -Remade", 640, 480);

	Sprite test("sprites/spr_player_default-Sheet.png",Vector2D(1,1));

	while (!gameManager->IsQuitting()){
		gameManager->Handle();
		gameManager->Update();
		test.Draw(Vector2D(0,0));
		gameManager->Render();
	}

	gameManager->Terminate();

	GameManager::Destroy();
	return 0;
}
