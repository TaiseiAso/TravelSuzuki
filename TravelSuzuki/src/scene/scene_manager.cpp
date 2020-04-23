#include <algorithm>
#include "scene_manager.h"
#include "DxLib.h"

namespace game::scene
{
	void SceneManager::initScene(const std::string& sceneName)
	{
		auto itr = nameToScene_.find(sceneName);
		if (itr != nameToScene_.end())
		{
			itr->second->initialize();
		}
	}

	void SceneManager::finalScene(const std::string& sceneName)
	{
		auto itr = nameToScene_.find(sceneName);
		if (itr != nameToScene_.end())
		{
			itr->second->finalize();
		}
	}

	void SceneManager::swapScene()
	{
		finalScene(currentSceneName_);
		currentSceneName_ = nextSceneName_;
		for (const std::string& deleteSceneName : deleteSceneNameVector_)
		{
			deleteScene(deleteSceneName);
		}
		deleteSceneNameVector_.clear();
		deleteSceneNameVector_.shrink_to_fit();
		initScene(currentSceneName_);
	}

	void SceneManager::updateMoveScene()
	{
		if (isMovingScene_)
		{
			if (moveSceneFrame_ == 0)
			{
				isMovingScene_ = false;
				swapScene();
			}
			else if (isFadeOut_)
			{
				++fadeLevel_;
				if (fadeLevel_ == moveSceneFrame_)
				{
					isFadeOut_ = false;
					swapScene();
				}
			}
			else
			{
				--fadeLevel_;
				if (fadeLevel_ == 0)
				{
					isMovingScene_ = false;
				}
			}
		}
	}

	void SceneManager::drawMoveSceneFade() const
	{
		if (isMovingScene_ && fadeLevel_ > 0 && moveSceneFrame_ > 0)
		{
			if ((isFadeOut_ && drawMoveSceneFadeOut_) || (!isFadeOut_ && drawMoveSceneFadeIn_))
			{
				int alpha = 255 * fadeLevel_ / moveSceneFrame_;
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::clamp<int>(alpha, 0, 255));
				DrawBox(0, 0, 800, 640, moveSceneFadeColor_, TRUE);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			}
		}
	}

	SceneManager::SceneManager()
		: isMovingScene_(false),
		  isFadeOut_(true),
		  moveSceneFrame_(0),
		  fadeLevel_(0),
		  drawMoveSceneFadeOut_(true),
		  drawMoveSceneFadeIn_(true),
		  moveSceneFadeColor_(GetColor(0, 0, 0))
	{}

	SceneManager::~SceneManager() {}

	bool SceneManager::step()
	{
		updateMoveScene();
		auto itr = nameToScene_.find(currentSceneName_);
		if (itr != nameToScene_.end())
		{
			if (!isMovingScene_) itr->second->action();
			itr->second->update();
			itr->second->draw();
			drawMoveSceneFade();
			return true;
		}
		else return false;
	}

	bool SceneManager::isMovingScene() const
	{
		return isMovingScene_;
	}

	float SceneManager::getFadeRatio() const
	{
		if (!isMovingScene_ || moveSceneFrame_ <= 0) return 0.f;
		float fadeRatio = (float)fadeLevel_ / moveSceneFrame_;
		return isFadeOut_ ? fadeRatio : -fadeRatio;
	}

	void SceneManager::setMoveSceneFrame(int moveSceneFrame)
	{
		if (!isMovingScene_) moveSceneFrame_ = moveSceneFrame;
	}

	void SceneManager::setDrawMoveSceneFade(bool drawMoveSceneFadeOut, bool drawMoveSceneFadeIn)
	{
		if (!isMovingScene_)
		{
			drawMoveSceneFadeOut_ = drawMoveSceneFadeOut;
			drawMoveSceneFadeIn_ = drawMoveSceneFadeIn;
		}
	}

	void SceneManager::setMoveSceneFadeColor(unsigned int moveSceneFadeColor)
	{
		if (!isMovingScene_) moveSceneFadeColor_ = moveSceneFadeColor;
	}

	void SceneManager::moveScene(const std::string& nextSceneName, const std::vector<std::string>& deleteSceneNameVector)
	{
		if (moveSceneFrame_ >= 0 && !isMovingScene_)
		{
			isMovingScene_ = true;
			nextSceneName_ = nextSceneName;
			isFadeOut_ = true;
			fadeLevel_ = 0;
			deleteSceneNameVector_ = deleteSceneNameVector;
		}
	}

	void SceneManager::deleteScene(const std::string& sceneName)
	{
		auto itr = nameToScene_.find(sceneName);
		if (itr != nameToScene_.end())
		{
			nameToScene_.erase(itr);
		}
	}
}