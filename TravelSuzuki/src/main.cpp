#include "game_core.h"
#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �Q�[�����쐬����
	game::GameCore gameCore;

	// �Q�[���̃��C�����[�v���J�n����
	gameCore.loop();

	return 0;
}