#include "base_scene.h"
#include <iostream>

namespace game::scene
{
	BaseScene::BaseScene(const std::shared_ptr<SceneMediator>& sceneMediator)
		: sceneMediator_(sceneMediator),
		  imagehandle_(-1)
	{}

	BaseScene::~BaseScene() {}
}