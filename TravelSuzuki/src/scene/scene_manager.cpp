#include "scene_manager.h"

namespace game::scene
{
	void SceneManager::createScene(SceneID sceneID)
	{
		auto itr = idToCreatedScene_.find(sceneID);
		if (itr == idToCreatedScene_.end())
		{
			std::unique_ptr<BaseScene> createdScene = sceneFactory_.createScene(sceneID, sceneMediator_);
			if (createdScene) idToCreatedScene_[sceneID] = std::move(createdScene);
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
		sceneMediator_->setAllowChangeVolumeFade(true, true); // テスト用
		sceneMediator_->setSceneMoveEffectID(SceneMoveEffectID::WHITE); // テスト用

		// 最初のシーン (テスト用)
		SceneID firstSceneID = SceneID::TITLE;

		createScene(firstSceneID);
		initScene(firstSceneID);
		currentSceneID_ = firstSceneID;
	}

	SceneManager::~SceneManager() {}

	bool SceneManager::step()
	{
		if (sceneMediator_->updateMoveScene()) moveScene();
		auto itr = idToCreatedScene_.find(currentSceneID_);
		if (itr != idToCreatedScene_.end())
		{
			if (!sceneMediator_->isMovingScene()) itr->second->action();
			itr->second->update();
			itr->second->draw();
			sceneMediator_->drawSceneMoveEffect();
			return true;
		}
		else return false;
	}
}