#include "game_scene.h"
#include "../input/input_receiver.h"
#include "DxLib.h"

namespace game::scene
{
	void GameScene::initialize()
	{

	}

	void GameScene::finalize()
	{

	}

	void GameScene::action()
	{
		if (input::InputReceiver::instance().isPushKeyNow(KEY_INPUT_Y))
		{
			sceneMediator_.lock()->moveScene(SceneID::TITLE, { SceneID::TITLE }, { SceneID::GAME });
		}
	}

	void GameScene::update()
	{

	}

	void GameScene::draw() const
	{

	}

	GameScene::GameScene(std::shared_ptr<SceneMediator>& sceneMediator)
		: BaseScene(sceneMediator)
	{

	}

	GameScene::~GameScene()
	{

	}
}