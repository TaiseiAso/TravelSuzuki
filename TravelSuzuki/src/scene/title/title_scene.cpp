#include "title_scene.h"
#include "device/graphic/image_manager.h"
#include "device/input/input_receiver.h"
#include "device/audio/music_player.h"
#include "scene/scene_manager.h"
#include "scene/battle/battle_scene.h"

namespace game::scene::title
{
	// ƒ^ƒCƒgƒ‹‰æ–Êê—p //////////////////////////////////////
	void TitleScene::actionPleasePressSpaceKey()
	{
		if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_SPACE))
			mode_ = Mode::MENU;
	}

	void TitleScene::actionMenu()
	{
		if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_UP))
		{
			if (cursor_ > 0) --cursor_;
		}
		else if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_DOWN))
		{
			if (cursor_ < 3) ++cursor_;
		}
		else if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_SPACE))
		{
			switch (cursor_)
			{
			case 0:
				SceneManager::instance().createScene<battle::BattleScene>("battle");
				SceneManager::instance().moveScene("battle", { "title" });
				break;
			case 1:
				SceneManager::instance().createScene<battle::BattleScene>("achievement");
				SceneManager::instance().moveScene("achievement", { "title" });
				break;
			case 2:
				cursor_ = 0;
				mode_ = Mode::FIRST;
				break;
			case 3:
				SceneManager::instance().setMoveSceneFrame(0);
				SceneManager::instance().moveScene("END");
			}
		}
	}

	void TitleScene::drawBackGround() const
	{
		// ”wŒi‚ð”’‚­‚·‚é
		DrawBox(0, 0, 800, 640, whiteColor_, TRUE);

		/*
		int up = 40 + static_cast<int>(10 * std::sin(elapsedFrame_ / 50.f));
		int down = 640 - up;
		int divX = 50;
		int divX2 = divX * 2;
		int divY = 50;
		int up2 = up + divY;
		int down2 = down - divY;
		int left = elapsedFrame_ % divX2;

		DrawBox(0, 0, 800, up, blueColor, TRUE);
		DrawBox(0, down, 800, 640, greenColor, TRUE);

		for (int i = -left; i < 800; i += divX2)
		{
			DrawTriangle(i, up, i + divX, up2, i + divX2, up, blueColor, TRUE);
			DrawTriangle(i, down, i + divX, down2, i + divX2, down, greenColor, TRUE);
		}
		*/
	}

	void TitleScene::drawTitleLogo() const
	{
		imagehandle_ = graphic::ImageManager::instance().getImageHandle("title_logo");
		//DrawGraph(100, 150 + static_cast<int>(20 * std::sin( elapsedFrame_ / 100.f)), imagehandle_, TRUE);
		DrawGraph(100, 150, imagehandle_, TRUE);
	}

	void TitleScene::drawPleasePressSpaceKey() const
	{
		DrawString(230, 400, "PLEASE PUSH SPACE KEY", blackColor_);
	}

	void TitleScene::drawMenu() const
	{
		DrawString(230, 360, "GAME START", cursor_ == 0 ? redColor_ : blackColor_);
		DrawString(230, 410, "ACHIEVEMENT", cursor_ == 1 ? redColor_ : blackColor_);
		DrawString(230, 460, "BACK", cursor_ == 2 ? redColor_ : blackColor_);
		DrawString(230, 510, "EXIT", cursor_ == 3 ? redColor_ : blackColor_);
	}
	//////////////////////////////////////////////////////////

	void TitleScene::initialize()
	{
		elapsedFrame_ = 0;
		SetFontSize(30);
	}

	void TitleScene::finalize()
	{

	}

	void TitleScene::action()
	{
		switch (mode_)
		{
		case Mode::FIRST:
			actionPleasePressSpaceKey();
			break;
		case Mode::MENU:
			actionMenu();
		}
	}

	void TitleScene::update()
	{
		++elapsedFrame_;
	}

	void TitleScene::draw() const
	{
		drawBackGround();
		drawTitleLogo();
		
		switch (mode_)
		{
		case Mode::FIRST:
			drawPleasePressSpaceKey();
			break;
		case Mode::MENU:
			drawMenu();
		}
	}

	TitleScene::TitleScene()
		: elapsedFrame_(0),
		  mode_(Mode::FIRST),
		  cursor_(0)
	{
		graphic::ImageManager::instance().loadImage("title_logo");
	}

	TitleScene::~TitleScene()
	{
		graphic::ImageManager::instance().deleteImage("title_logo");
	}
}