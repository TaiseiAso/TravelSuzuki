#include "base_scene.h"

namespace game::scene
{
	BaseScene::BaseScene(std::shared_ptr<SceneMediator>& sceneMediator)
		: sceneMediator_(sceneMediator),
		  Imagehandle_(-1),
		  elapsedFrame_(0)
	{

	}

	BaseScene::~BaseScene()
	{

	}

	void BaseScene::baseUpdate()
	{
		update();
		if (++elapsedFrame_ == INT_MAX) elapsedFrame_ = 0;
	}
}