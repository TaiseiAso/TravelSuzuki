#include "game_core.h"
#include "DxLib.h"
#include "input/input_receiver.h"
#include "audio/music_player.h"
#include "graphic/image_manager.h"

namespace game
{
	GameCore::GameCore()
	{
		SetOutApplicationLogValidFlag(FALSE); //Log.txtを生成しないように設定
		SetMainWindowText("Travel Suzuki"); // タイトルを設定
		ChangeWindowMode(TRUE); // ウィンドウモードに設定
		SetGraphMode(800, 640, 32); //画面サイズ指定

		DxLib_Init(); // DXライブラリ初期化処理

		SetDrawScreen(DX_SCREEN_BACK); // 描画先を裏画面にする
	
		input::InputReceiver::create();
		audio::MusicPlayer::create();
		audio::MusicPlayer::instance().loadMusicNameToPathDatabase("resource/database/music_name_to_path.csv");
		graphic::ImageManager::create();
		graphic::ImageManager::instance().loadImageNameToPathDatabase("resource/database/image_name_to_path.csv");
		graphic::ImageManager::instance().loadGroupNameToDivDataDatabase("resource/database/group_name_to_divdata.csv");
		graphic::ImageManager::instance().loadGroupNameToFramesDatabase("resource/database/group_name_to_frames.csv");

		fpsController_ = std::make_unique<fps::FPSController>();
		sceneManager_ = std::make_unique<scene::SceneManager>();
	}

	GameCore::~GameCore()
	{
		sceneManager_.reset();

		graphic::ImageManager::destroy();
		audio::MusicPlayer::destroy();
		input::InputReceiver::destroy();

		DxLib_End(); // DXライブラリ終了処理
	}

	void GameCore::loop()
	{
		while (!ProcessMessage())
		{
			fpsController_->update();
			input::InputReceiver::instance().update();

			ClearDrawScreen();
			
			sceneManager_->step();
			fpsController_->draw(); // テスト用
			
			ScreenFlip();
			
			fpsController_->wait();
		}
	}
}