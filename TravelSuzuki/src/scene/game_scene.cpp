#include "game_scene.h"
#include "../input/input_receiver.h"
#include "DxLib.h"

namespace game::scene
{
	void GameScene::init()
	{

	}

	void GameScene::action()
	{
		if (input::InputReceiver::instance().getPushKeyFrame(KEY_INPUT_Y) == 1)
		{
		sceneMediator_->moveScene(SceneID::TITLE, 60, { SceneID::TITLE }, { SceneID::GAME });
		}
	}

	void GameScene::update()
	{

	}

	void GameScene::draw() const
	{

	}

	GameScene::GameScene(std::shared_ptr<SceneMediator> sceneMediator) : BaseScene(sceneMediator)
	{

	}

	GameScene::~GameScene()
	{

	}
}