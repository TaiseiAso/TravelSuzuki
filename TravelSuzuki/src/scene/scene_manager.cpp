#include <algorithm>
#include "scene_manager.h"
#include "../audio/music_player.h"
#include "DxLib.h"

namespace game::scene
{
	void SceneManager::initScene(std::string sceneName)
	{
		auto itr = nameToScene_.find(sceneName);
		if (itr != nameToScene_.end())
		{
			itr->second->initialize();
		}
	}

	void SceneManager::finalScene(std::string sceneName)
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
		initScene(currentSceneName_);
		for (const std::string& deleteSceneName : deleteSceneNameVector_)
		{
			deleteScene(deleteSceneName);
		}
		deleteSceneNameVector_.clear();
		deleteSceneNameVector_.shrink_to_fit();
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
				if (allowChangeVolumeFadeOut_)
				{
					audio::MusicPlayer::instance().setFadeVolume(
						1.f - (float)fadeLevel_ / moveSceneFrame_
					);
				}
				if (fadeLevel_ == moveSceneFrame_)
				{
					isFadeOut_ = false;
					if (!allowChangeVolumeFadeIn_)
					{
						audio::MusicPlayer::instance().setFadeVolume(1.f);
					}
					swapScene();
				}
			}
			else
			{
				--fadeLevel_;
				if (allowChangeVolumeFadeIn_)
				{
					audio::MusicPlayer::instance().setFadeVolume(
						1.f - (float)fadeLevel_ / moveSceneFrame_
					);
				}
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
		  allowChangeVolumeFadeOut_(true),
		  allowChangeVolumeFadeIn_(true),
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

	void SceneManager::setAllowChangeVolumeFade(bool allowChangeVolumeFadeOut, bool allowChangeVolumeFadeIn)
	{
		if (!isMovingScene_)
		{
			allowChangeVolumeFadeOut_ = allowChangeVolumeFadeOut;
			allowChangeVolumeFadeIn_ = allowChangeVolumeFadeIn;
		}
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

	void SceneManager::moveScene(std::string nextSceneName, const std::vector<std::string>& deleteSceneNameVector)
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

	void SceneManager::deleteScene(std::string sceneName)
	{
		auto itr = nameToScene_.find(sceneName);
		if (itr != nameToScene_.end())
		{
			nameToScene_.erase(itr);
		}
	}
}