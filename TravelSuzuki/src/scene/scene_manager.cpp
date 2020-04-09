#include "scene_manager.h"
#include "../input/input_receiver.h"

namespace game::scene
{
	void SceneManager::action()
	{
		currentScene_->action();
	}

	void SceneManager::update()
	{
		currentScene_->update();
	}

	void SceneManager::draw() const
	{
		currentScene_->draw();
	}

	SceneManager::SceneManager()
		: sceneFactory_(std::make_unique<SceneFactory>()),
		  currentScene_(sceneFactory_->create(SceneID::TITLE))
	{
		input::InputReceiver::instance().create();
	}

	SceneManager::~SceneManager()
	{
		input::InputReceiver::instance().destroy();
	}

	void SceneManager::step()
	{
		input::InputReceiver::instance().update();
		action();
		update();
		draw();
	}
}