#include "game_core.h"
#include "DxLib.h"
#include "device/input/input_receiver.h"
#include "device/audio/music_player.h"
#include "device/graphic/image_manager.h"
#include "device/text/font_manager.h"
#include "scene/scene_manager.h"
#include "scene/test/test_scene.h"

namespace game
{
	GameCore::GameCore()
		: fpsController_(std::make_unique<fps::FPSController>())
	{
		SetOutApplicationLogValidFlag(FALSE); //Log.txtを生成しないように設定
		SetMainWindowText("Travel Suzuki"); // タイトルを設定
		ChangeWindowMode(TRUE); // ウィンドウモードに設定
		SetGraphMode(800, 640, 32); //画面サイズ指定

		DxLib_Init(); // DXライブラリ初期化処理

		SetDrawScreen(DX_SCREEN_BACK); // 描画先を裏画面にする

		input::InputReceiver::create();
		audio::MusicPlayer::create();
		graphic::ImageManager::create();
		text::FontManager::create();

		audio::MusicPlayer::instance().loadMusicNameToPathDatabase("resource/database/music_name_to_path.csv");
		graphic::ImageManager::instance().loadImageNameToPathDatabase("resource/database/image_name_to_path.csv");
		graphic::ImageManager::instance().loadGroupNameToDivDataDatabase("resource/database/group_name_to_divdata.csv");
		graphic::ImageManager::instance().loadGroupNameToFramesDatabase("resource/database/group_name_to_frames.csv");
		text::FontManager::instance().loadFontResourceNameToPathDatabase("resource/database/font_resource_name_to_path.csv");

		scene::SceneManager::create();
		scene::SceneManager::instance().createFirstScene<scene::test::TestScene>("test");

		// テスト用
		scene::SceneManager::instance().setMoveSceneFadeColor(GetColor(255, 255, 255));
		scene::SceneManager::instance().setMoveSceneFrame(60);
	}

	GameCore::~GameCore()
	{
		scene::SceneManager::destroy();

		text::FontManager::destroy();
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
			audio::MusicPlayer::instance().updateFadeMusicVolume();

			ClearDrawScreen();
			
			if (!scene::SceneManager::instance().step()) break;
			fpsController_->draw(); // テスト用
			
			ScreenFlip();
			
			fpsController_->wait();
		}
	}
}