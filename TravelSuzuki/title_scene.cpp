#include "title_scene.h"

namespace game::scene
{
	void TitleScene::action()
	{

	}

	void TitleScene::update()
	{

	}

	void TitleScene::draw() const
	{
		DrawCircle(100, 100, 100, GetColor(255, 255, 255), 1, 1);
	}

	TitleScene::TitleScene()
	{

	}

	TitleScene::~TitleScene()
	{

	}
}