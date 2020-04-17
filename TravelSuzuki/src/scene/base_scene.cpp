#include "base_scene.h"

namespace game::scene
{
	void BaseScene::baseInitialize()
	{
		elapsedFrame_ = 0;
		initialize();
	}

	void BaseScene::baseFinalize()
	{
		finalize();
	}

	void BaseScene::baseAction()
	{
		action();
	}

	void BaseScene::baseUpdate()
	{
		update();
		if (++elapsedFrame_ == INT_MAX) elapsedFrame_ = 0;
	}

	void BaseScene::baseDraw()
	{
		draw();
	}

	BaseScene::BaseScene(std::shared_ptr<SceneMediator>& sceneMediator)
		: sceneMediator_(sceneMediator),
		  Imagehandle_(-1),
		  elapsedFrame_(0)
	{}

	BaseScene::~BaseScene() {}
}