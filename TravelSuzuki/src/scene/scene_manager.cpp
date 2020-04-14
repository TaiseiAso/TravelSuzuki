#include "scene_manager.h"

namespace game::scene
{
	void SceneManager::createScene(SceneID sceneID)
	{
		auto itr = idToCreatedScene_.find(sceneID);
		if (itr == idToCreatedScene_.end())
		{
			switch (sceneID)
			{
			case SceneID::TITLE:
				idToCreatedScene_[sceneID] = std::make_unique<TitleScene>(sceneMediator_);
				break;
			case SceneID::GAME:
				idToCreatedScene_[sceneID] = std::make_unique<GameScene>(sceneMediator_);
				break;
			case SceneID::RESULT:
				idToCreatedScene_[sceneID] = std::make_unique<ResultScene>(sceneMediator_);
				break;
			case SceneID::ACHIEVEMENT:
				idToCreatedScene_[sceneID] = std::make_unique<AchievementScene>(sceneMediator_);
			}
		}
	}

	void SceneManager::initScene(SceneID sceneID)
	{
		auto itr = idToCreatedScene_.find(sceneID);
		if (itr != idToCreatedScene_.end())
		{
			itr->second->init();
		}
	}

	void SceneManager::deleteScene(SceneID sceneID)
	{
		auto itr = idToCreatedScene_.find(sceneID);
		if (itr != idToCreatedScene_.end())
		{
			idToCreatedScene_.erase(itr);
		}
	}

	void SceneManager::moveScene()
	{
		SceneID nextSceneID = sceneMediator_->getNextSceneID();
		std::vector<SceneID> createSceneIDVector = sceneMediator_->getCreateSceneIDVector();
		std::vector<SceneID> deleteSceneIDVector = sceneMediator_->getDeleteSceneIDVector();

		for (const SceneID& createSceneID : createSceneIDVector)
		{
			createScene(createSceneID);
		}

		currentSceneID_ = nextSceneID;
		initScene(currentSceneID_);

		for (const SceneID& deleteSceneID : deleteSceneIDVector)
		{
			deleteScene(deleteSceneID);
		}
	}

	SceneManager::SceneManager()
	{
		sceneMediator_ = std::make_shared<SceneMediator>();
		createScene(SceneID::TITLE);
		initScene(SceneID::TITLE);
		currentSceneID_ = SceneID::TITLE;
	}

	SceneManager::~SceneManager()
	{
		sceneMediator_.reset();
	}

	void SceneManager::step()
	{
		if (sceneMediator_->update()) moveScene();
		auto itr = idToCreatedScene_.find(currentSceneID_);
		if (itr != idToCreatedScene_.end())
		{
			if (!sceneMediator_->isMovingScene()) itr->second->action();
			itr->second->update();
			itr->second->draw();
			sceneMediator_->draw();
		}
	}
}