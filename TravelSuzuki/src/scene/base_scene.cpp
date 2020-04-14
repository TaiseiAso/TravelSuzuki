#include "base_scene.h"

namespace game::scene
{
	BaseScene::BaseScene(std::shared_ptr<SceneMediator> sceneMediator)
	{
		sceneMediator_ = sceneMediator;
	}

	BaseScene::~BaseScene()
	{
	}
}