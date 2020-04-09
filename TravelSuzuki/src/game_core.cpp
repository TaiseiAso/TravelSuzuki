#include "game_core.h"
#include "DxLib.h"
#include "input/input_receiver.h"
#include "audio/music_player.h"

namespace game
{
	GameCore::GameCore()
	{
		SetOutApplicationLogValidFlag(FALSE); //Log.txt�𐶐����Ȃ��悤�ɐݒ�
		SetMainWindowText("Travel Suzuki"); // �^�C�g����ݒ�
		ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ɐݒ�
		SetGraphMode(800, 640, 32); //��ʃT�C�Y�w��

		DxLib_Init(); // DX���C�u��������������

		SetDrawScreen(DX_SCREEN_BACK); // �`���𗠉�ʂɂ���
	
		input::InputReceiver::create();
		audio::MusicPlayer::create();

		fpsController_ = std::make_unique<fps::FPSController>();
		sceneManager_ = std::make_unique<scene::SceneManager>();
	}

	GameCore::~GameCore()
	{
		sceneManager_.reset();
		fpsController_.reset();

		audio::MusicPlayer::destroy();
		input::InputReceiver::destroy();

		DxLib_End(); // DX���C�u�����I������
	}

	void GameCore::loop()
	{
		while (!ProcessMessage())
		{
			fpsController_->update();
			input::InputReceiver::instance().update();
			ClearDrawScreen();
			sceneManager_->step();
			fpsController_->draw(); // �e�X�g�p
			ScreenFlip();
			fpsController_->wait();
		}
	}
}