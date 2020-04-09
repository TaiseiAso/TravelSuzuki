#include "title_scene.h"
#include "../input/input_receiver.h"
#include "DxLib.h"
#include <sstream>

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
		DrawBox(200, 200, 230, 230, GetColor(0, 0, 0), TRUE);

		DrawFormatString(200, 200, GetColor(255, 255, 255), "%d",
			input::InputReceiver::instance().getPushKeyFrame(KEY_INPUT_SPACE)
		);
	}

	TitleScene::TitleScene()
	{
	}

	TitleScene::~TitleScene()
	{
	}
}