#include "stage_scene.h"
#include "device/input/input_receiver.h"
#include "game_manager.h"

namespace game::scene::stage
{
	void StageScene::initialize()
	{
		player_->initialize();
	}

	void StageScene::finalize()
	{
		player_->finalize();
	}

	void StageScene::action()
	{
		if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_SPACE))
		{
			if (GameManager::instance().getTimerRef().isStop())
			{
				GameManager::instance().getTimerRef().resume();
			}
			else
			{
				GameManager::instance().getTimerRef().stop();
			}
		}

		GameManager::instance().action();
		player_->action();
	}

	void StageScene::update()
	{
		GameManager::instance().update();
		player_->update();
	}

	void StageScene::draw() const
	{
		DrawBox(0, 0, 800, 640, whiteColor_, TRUE);
		GameManager::instance().draw();
		player_->draw();
	}

	StageScene::StageScene()
		: blockFactory_(std::make_unique<object::block::BlockFactory>()),
		  player_(std::make_shared<object::character::player::Player>())
	{

	}

	StageScene::~StageScene()
	{

	}
}