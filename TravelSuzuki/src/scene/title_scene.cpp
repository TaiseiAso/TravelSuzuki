#include "title_scene.h"
#include "../input/input_receiver.h"
#include "../audio/music_player.h"
#include "DxLib.h"

namespace game::scene
{
	void TitleScene::action()
	{
		if (input::InputReceiver::instance().getPushKeyFrame(KEY_INPUT_P) == 1)
		{
			audio::MusicPlayer::instance().playMusic("test", "test1", 255, true, true);
		}
		else if (input::InputReceiver::instance().getPushKeyFrame(KEY_INPUT_S) == 1)
		{
			audio::MusicPlayer::instance().stopMusic("test1");
		}
		else if (input::InputReceiver::instance().getPushKeyFrame(KEY_INPUT_Q) == 1)
		{
			audio::MusicPlayer::instance().setPlayMusicVolume("test1", 120);
		}
		else if (input::InputReceiver::instance().getPushKeyFrame(KEY_INPUT_W) == 1)
		{
			audio::MusicPlayer::instance().setPlayMusicVolume("test1", 255);
		}
		else if (input::InputReceiver::instance().getPushKeyFrame(KEY_INPUT_E) == 1)
		{
			audio::MusicPlayer::instance().setMasterVolume(0.5f);
		}
		else if (input::InputReceiver::instance().getPushKeyFrame(KEY_INPUT_R) == 1)
		{
			audio::MusicPlayer::instance().setMasterVolume(1.f);
		}
	}

	void TitleScene::update()
	{

	}

	void TitleScene::draw() const
	{
		DrawCircle(100, 100, 100, GetColor(255, 255, 255), 1, 1);
		DrawBox(200, 200, 230, 230, GetColor(0, 0, 0), TRUE);

		DrawFormatString(
			200, 200, GetColor(255, 255, 255),
			"%d", input::InputReceiver::instance().getPushKeyFrame(KEY_INPUT_SPACE)
		);
	}

	TitleScene::TitleScene()
	{
		audio::MusicPlayer::instance().loadMusic("test");
	}

	TitleScene::~TitleScene()
	{
		audio::MusicPlayer::instance().deleteMusic("test");
	}
}