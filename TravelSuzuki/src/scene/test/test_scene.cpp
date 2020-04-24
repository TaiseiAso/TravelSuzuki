#include "test_scene.h"
#include "device/input/input_receiver.h"
#include "device/audio/music_player.h"
#include "scene/scene_manager.h"
#include "scene/title/title_scene.h"
#include "DxLib.h"

namespace game::scene::test
{
	void TestScene::initialize()
	{

	}

	void TestScene::finalize()
	{
		audio::MusicPlayer::instance().stopMusic("test1");
	}

	void TestScene::action()
	{
		if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_P))
		{
			audio::MusicPlayer::instance().playMusic("test", "test1", 255, true, true);
		}
		else if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_S))
		{
			audio::MusicPlayer::instance().stopMusic("test1");
		}
		else if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_Q))
		{
			audio::MusicPlayer::instance().setPlayMusicVolume("test1", 120);
		}
		else if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_W))
		{
			audio::MusicPlayer::instance().setPlayMusicVolume("test1", 255);
		}
		else if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_E))
		{
			audio::MusicPlayer::instance().setMasterVolume(0.5f);
		}
		else if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_R))
		{
			audio::MusicPlayer::instance().setMasterVolume(1.f);
		}
		else if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_T))
		{
			audio::MusicPlayer::instance().deleteAllMusic();
		}
		else if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_Y))
		{
			SceneManager::instance().createScene<title::TitleScene>("title");
			SceneManager::instance().moveScene("title", { "test" });
		}
		else if (input::InputReceiver::instance().isPushingKey(KEY_INPUT_U))
		{
			if (++elapsedFrame_ == INT_MAX) elapsedFrame_ = 0;
			audio::MusicPlayer::instance().setPlayMusicDistance("test1", 200 * std::abs(std::sinf(elapsedFrame_ / 30.f)));
		}
		else if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_I))
		{
			audio::MusicPlayer::instance().startFadeMusicVolume("test1", 100, 60);
		}
		else if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_O))
		{
			audio::MusicPlayer::instance().startFadeMusicVolume("test1", 255, 60);
		}
	}

	void TestScene::update()
	{

	}

	void TestScene::draw() const
	{
		DrawCircle(100, 100, 100, GetColor(255, 255, 255), 1, 1);
		DrawBox(200, 200, 230, 230, GetColor(0, 0, 0), TRUE);

		DrawFormatString(
			200, 200, GetColor(255, 255, 255),
			"%d", input::InputReceiver::instance().getPushKeyFrame(KEY_INPUT_SPACE)
		);

		int handle;
		handle = graphic::ImageManager::instance().getImageHandle("test");
		DrawGraph(300, 300, handle, TRUE);

		handle = graphic::ImageManager::instance().getImageHandleInGroup("test", 2);
		DrawGraph(300, 000, handle, TRUE);

		handle = graphic::ImageManager::instance().getImageHandleInAnime("test", &testElapsedData_);
		DrawGraph(0, 300, handle, TRUE);

		DrawCircle(
			450 + (int)(SceneManager::instance().getFadeRatio() * 450),
			500, 30, GetColor(255, 255, 255), 1, 1);

		DrawCircle(
			400 + (int)(200 * std::sinf(elapsedFrame_ / 30.f)),
			200, 30, GetColor(0, 255, 255), 1, 1);
	}

	TestScene::TestScene()
		: elapsedFrame_(0)
	{
		audio::MusicPlayer::instance().loadMusic("test");
		graphic::ImageManager::instance().loadImage("test");
		graphic::ImageManager::instance().loadGroup("test");

		testElapsedData_ = { 0, 0 };

		audio::MusicPlayer::instance().setVolumeAttenuationCoefficient(200.f);
	}

	TestScene::~TestScene()
	{
		audio::MusicPlayer::instance().deleteMusic("test");
		graphic::ImageManager::instance().deleteImage("test");
		graphic::ImageManager::instance().deleteGroup("test");
	}
}