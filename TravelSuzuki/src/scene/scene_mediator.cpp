#include <algorithm>
#include "scene_mediator.h"
#include "../audio/music_player.h"
#include "DxLib.h"

namespace game::scene
{
	void SceneMediator::drawScreenOneColor(unsigned int color) const
	{
		int alpha = 255 * moveSceneData_.fadeLevel / moveSceneData_.moveSceneFrame;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::clamp<int>(alpha, 0, 255));
		DrawBox(0, 0, 800, 640, color, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}

	SceneMediator::SceneMediator()
	{
		moveSceneData_.isMovingScene = false;
		moveSceneData_.moveSceneFrame = 0;
		moveSceneData_.allowChangeVolumeFadeOut = false;
		moveSceneData_.allowChangeVolumeFadeIn = false;
		moveSceneData_.sceneMoveEffectID = SceneMoveEffectID::WHITE;
	}

	SceneMediator::~SceneMediator() {}

	bool SceneMediator::isMovingScene() const
	{
		return moveSceneData_.isMovingScene;
	}

	SceneID SceneMediator::getNextSceneID() const
	{
		return moveSceneData_.nextSceneID;
	}

	const std::vector<SceneID>& SceneMediator::getCreateSceneIDVector() const
	{
		return moveSceneData_.createSceneIDVector;
	}

	const std::vector<SceneID>& SceneMediator::getDeleteSceneIDVector() const
	{
		return moveSceneData_.deleteSceneIDVector;
	}

	float SceneMediator::getFadeRatio() const
	{
		if (!moveSceneData_.isMovingScene || moveSceneData_.moveSceneFrame <= 0) return 0.f;
		float fadeRatio = (float)moveSceneData_.fadeLevel / moveSceneData_.moveSceneFrame;
		return moveSceneData_.isFadeOut ? fadeRatio : -fadeRatio;
	}

	void SceneMediator::setMoveSceneFrame(int moveSceneFrame)
	{
		if (!moveSceneData_.isMovingScene) moveSceneData_.moveSceneFrame = moveSceneFrame;
	}

	void SceneMediator::setAllowChangeVolumeFade(bool allowChangeVolumeFadeOut, bool allowChangeVolumeFadeIn)
	{
		if (!moveSceneData_.isMovingScene)
		{
			moveSceneData_.allowChangeVolumeFadeOut = allowChangeVolumeFadeOut;
			moveSceneData_.allowChangeVolumeFadeIn = allowChangeVolumeFadeIn;
		}
	}

	void SceneMediator::setSceneMoveEffectID(SceneMoveEffectID sceneMoveEffectID)
	{
		if (!moveSceneData_.isMovingScene) moveSceneData_.sceneMoveEffectID = sceneMoveEffectID;
	}

	void SceneMediator::moveScene(SceneID nextSceneID)
	{
		moveScene(nextSceneID, {}, {});
	}

	void SceneMediator::moveScene(SceneID nextSceneID, const std::vector<SceneID>& createSceneIDVector, const std::vector<SceneID>& deleteSceneIDVector)
	{
		if (moveSceneData_.moveSceneFrame >= 0 && !moveSceneData_.isMovingScene)
		{
			moveSceneData_.createSceneIDVector.clear();
			moveSceneData_.createSceneIDVector.shrink_to_fit();
			moveSceneData_.deleteSceneIDVector.clear();
			moveSceneData_.deleteSceneIDVector.shrink_to_fit();

			moveSceneData_.isMovingScene = true;
			moveSceneData_.nextSceneID = nextSceneID;
			moveSceneData_.isFadeOut = true;
			moveSceneData_.fadeLevel = 0;
			moveSceneData_.createSceneIDVector = createSceneIDVector;
			moveSceneData_.deleteSceneIDVector = deleteSceneIDVector;
		}
	}

	bool SceneMediator::updateMoveScene()
	{
		if (moveSceneData_.isMovingScene)
		{
			if (moveSceneData_.moveSceneFrame == 0)
			{
				moveSceneData_.isMovingScene = false;
				return true;
			}
			
			if (moveSceneData_.isFadeOut)
			{
				++moveSceneData_.fadeLevel;
				if (moveSceneData_.allowChangeVolumeFadeOut)
				{
					audio::MusicPlayer::instance().setFadeVolume(
						1.f - (float)moveSceneData_.fadeLevel / moveSceneData_.moveSceneFrame
					);
				}
				if (moveSceneData_.fadeLevel == moveSceneData_.moveSceneFrame)
				{
					moveSceneData_.isFadeOut = false;
					if (!moveSceneData_.allowChangeVolumeFadeIn)
					{
						audio::MusicPlayer::instance().setFadeVolume(1.f);
					}
					return true;
				}
			}
			else
			{
				--moveSceneData_.fadeLevel;
				if (moveSceneData_.allowChangeVolumeFadeIn)
				{
					audio::MusicPlayer::instance().setFadeVolume(
						1.f - (float)moveSceneData_.fadeLevel / moveSceneData_.moveSceneFrame
					);
				}
				if (moveSceneData_.fadeLevel == 0)
				{
					moveSceneData_.isMovingScene = false;
				}
			}
		}
		return false;
	}

	void SceneMediator::drawSceneMoveEffect() const
	{
		if (moveSceneData_.isMovingScene && moveSceneData_.fadeLevel > 0 && moveSceneData_.moveSceneFrame > 0)
		{
			switch (moveSceneData_.sceneMoveEffectID)
			{
			case SceneMoveEffectID::BLACK:
				drawScreenOneColor(GetColor(0, 0, 0));
				break;
			case SceneMoveEffectID::WHITE:
				drawScreenOneColor(GetColor(255, 255, 255));
				break;
			}
		}
	}
}