#include "../Header/Util/pch.h"
#include "../Header/Scene/MainScene.h"
#include "../Header/Scene/GameScene.h"

int main() {
	Program_Init();

	MainScene_Init();
	GameScene_Init();

	int sceneInfo = MAIN_SCENE;

	while (sceneInfo >= 0) {
		switch (sceneInfo) {
			case MAIN_SCENE :
				sceneInfo = MainScene_Loop();
				break;
			case GAME_SCENE :
				sceneInfo = GameScene_Loop();
				break;
			default :
				sceneInfo = EXIT_GAME;
				break;
		}
	}

	MainScene_Release();
	GameScene_Release();

	Program_Release();
	return 0;
}
