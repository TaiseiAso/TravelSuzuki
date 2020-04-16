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
			case SceneID::TEST:
				idToCreatedScene_[sceneID] = std::make_unique<TestScene>(sceneMediator_);
				break;
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
			itr->second->initialize();
		}
	}

	void SceneManager::finalScene(SceneID sceneID)
	{
		auto itr = idToCreatedScene_.find(sceneID);
		if (itr != idToCreatedScene_.end())
		{
			itr->second->finalize();
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
		const std::vector<SceneID>& createSceneIDVector = sceneMediator_->getCreateSceneIDVector();
		const std::vector<SceneID>& deleteSceneIDVector = sceneMediator_->getDeleteSceneIDVector();

		finalScene(currentSceneID_);

		for (const SceneID& createSceneID : createSceneIDVector)
		{
			createScene(createSceneID);
		}

		currentSceneID_ = nextSceneID;

		for (const SceneID& deleteSceneID : deleteSceneIDVector)
		{
			deleteScene(deleteSceneID);
		}

		initScene(currentSceneID_);
	}

	SceneManager::SceneManager()
	{
		sceneMediator_ = std::make_shared<SceneMediator>();
		sceneMediator_->setMoveSceneFrame(60); // テスト用
		sceneMediator_->setAllowChangeMasterVolumeFade(true, true); // テスト用
		sceneMediator_->setSceneMoveEffectID(SceneMoveEffectID::WHITE); // テスト用

		// 最初のシーン (テスト用)
		SceneID firstSceneID = SceneID::TEST;

		createScene(firstSceneID);
		initScene(firstSceneID);
		currentSceneID_ = firstSceneID;
	}

	SceneManager::~SceneManager() {}

	void SceneManager::step()
	{
		if (sceneMediator_->updateMoveScene()) moveScene();
		auto itr = idToCreatedScene_.find(currentSceneID_);
		if (itr != idToCreatedScene_.end())
		{
			if (!sceneMediator_->isMovingScene()) itr->second->action();
			itr->second->baseUpdate();
			itr->second->draw();
			sceneMediator_->drawSceneMoveEffect();
		}
	}
}