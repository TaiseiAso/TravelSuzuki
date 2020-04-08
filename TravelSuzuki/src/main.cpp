#include "game_core.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ゲームを作成する
	game::GameCore gameCore;

	// ゲームのメインループを開始する
	gameCore.loop();

	return 0;
}