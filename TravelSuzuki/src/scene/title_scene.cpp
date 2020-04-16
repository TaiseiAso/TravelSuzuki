#include "title_scene.h"
#include "../graphic/image_manager.h"
#include "../input/input_receiver.h"
#include "../audio/music_player.h"

namespace game::scene
{
	// タイトル画面専用 //////////////////////////////////////
	void TitleScene::drawBackGround() const
	{
		// 背景を白くする
		DrawBox(0, 0, 800, 640, whiteColor, TRUE);

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
	}

	void TitleScene::drawTitleLogo() const
	{
		Imagehandle_ = graphic::ImageManager::instance().getImageHandle("title_logo");
		DrawGraph(100, 150 + static_cast<int>(20 * std::sin( elapsedFrame_ / 100.f)), Imagehandle_, TRUE);
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

	}

	void TitleScene::update()
	{
		
	}

	void TitleScene::draw() const
	{
		drawBackGround();
		drawTitleLogo();
	}

	TitleScene::TitleScene(std::shared_ptr<SceneMediator>& sceneMediator)
		: BaseScene(sceneMediator)
	{
		graphic::ImageManager::instance().loadImage("title_logo");
	}

	TitleScene::~TitleScene()
	{
		graphic::ImageManager::instance().deleteImage("title_logo");
	}
}