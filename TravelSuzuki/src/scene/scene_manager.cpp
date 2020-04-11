#include "scene_manager.h"

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
	{
		sceneFactory_ = std::make_unique<SceneFactory>();
		currentScene_ = sceneFactory_->create(SceneID::TITLE);
	}

	SceneManager::~SceneManager()
	{
		currentScene_.reset();
		sceneFactory_.reset();
	}

	void SceneManager::step()
	{
		action();
		update();
		draw();
	}
}