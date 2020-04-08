#include "game_core.h"

namespace game
{
	GameCore::GameCore()
		:	fpsController_(std::make_unique<FPSController>()),
			sceneManager_(std::make_unique<scene::SceneManager>())
	{
		SetOutApplicationLogValidFlag(FALSE); //Log.txtを生成しないように設定
		ChangeWindowMode(TRUE); // ウィンドウモードに設定
		SetGraphMode(800, 640, 32); //画面サイズ指定

		DxLib_Init(); // DXライブラリ初期化処理

		SetDrawScreen(DX_SCREEN_BACK); // 描画先を裏画面にする
	}

	GameCore::~GameCore()
	{
		DxLib_End(); // DXライブラリ終了処理
	}

	void GameCore::loop()
	{
		while (!ProcessMessage())
		{
			fpsController_->update();
			ClearDrawScreen();
			sceneManager_->step();
			fpsController_->draw(); // テスト用
			ScreenFlip();
			fpsController_->wait();
		}
	}
}