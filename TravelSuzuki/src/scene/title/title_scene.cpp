#include "title_scene.h"
#include "device/graphic/image_manager.h"
#include "device/input/input_receiver.h"
#include "device/audio/music_player.h"
#include "device/text/font_manager.h"
#include "scene/scene_manager.h"
#include "scene/battle/battle_scene.h"

namespace game::scene::title
{
	// タイトル画面専用 //////////////////////////////////////
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
		// 背景を白くする
		DrawBox(0, 0, 800, 640, whiteColor_, TRUE);
	}

	void TitleScene::drawTitleLogo() const
	{
		imagehandle_ = graphic::ImageManager::instance().getImageHandle("title_logo");
		DrawGraph(100, 150, imagehandle_, TRUE);
	}

	void TitleScene::drawPleasePressSpaceKey() const
	{
		int fontHandle = text::FontManager::instance().getFontHandle("test");
		DrawStringToHandle(230, 400, "PLEASE PUSH SPACE KEY", blackColor_, fontHandle);
	}

	void TitleScene::drawMenu() const
	{
		int fontHandle = text::FontManager::instance().getFontHandle("test");
		DrawStringToHandle(230, 360, "GAME START スタート", cursor_ == 0 ? redColor_ : blackColor_, fontHandle);
		DrawStringToHandle(230, 410, "ACHIEVEMENT", cursor_ == 1 ? redColor_ : blackColor_, fontHandle);
		DrawStringToHandle(230, 460, "BACK", cursor_ == 2 ? redColor_ : blackColor_, fontHandle);
		DrawStringToHandle(230, 510, "EXIT", cursor_ == 3 ? redColor_ : blackColor_, fontHandle);
	}
	//////////////////////////////////////////////////////////

	void TitleScene::initialize()
	{
		elapsedFrame_ = 0;
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
		text::FontManager::instance().loadFontResourceFromNameWithDatabase("Voyager Grotesque Bold");
		text::FontManager::instance().createFont("Voyager Grotesque Bold", "test", 32, 6, DX_FONTTYPE_ANTIALIASING);
	}

	TitleScene::~TitleScene()
	{
		graphic::ImageManager::instance().deleteImage("title_logo");
		text::FontManager::instance().deleteFont("Voyager Grotesque Bold");
		text::FontManager::instance().deleteFontResourceFromNameWithDatabase("Voyager Grotesque Bold");
	}
}