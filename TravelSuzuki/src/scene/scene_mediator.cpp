#include "scene_mediator.h"
#include "../audio/music_player.h"
#include "DxLib.h"

namespace game::scene
{
	void SceneMediator::drawScreenOneColor(unsigned int color) const
	{
		int alpha = 255 * moveSceneData_.fadeLevel / moveSceneData_.moveSceneFrame;
		if (alpha < 0) alpha = 0;
		else if (alpha > 255) alpha = 255;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawBox(0, 0, 800, 640, color, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}

	SceneMediator::SceneMediator()
	{
		moveSceneData_.isMovingScene = false;
		moveSceneData_.moveSceneFrame = 0;
		moveSceneData_.allowChangeMasterVolumeFadeOut = false;
		moveSceneData_.allowChangeMasterVolumeFadeIn = false;
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

	void SceneMediator::setAllowChangeMasterVolumeFade(bool allowChangeMasterVolumeFadeOut, bool allowChangeMasterVolumeFadeIn)
	{
		if (!moveSceneData_.isMovingScene)
		{
			moveSceneData_.allowChangeMasterVolumeFadeOut = allowChangeMasterVolumeFadeOut;
			moveSceneData_.allowChangeMasterVolumeFadeIn = allowChangeMasterVolumeFadeIn;
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

	void SceneMediator::moveScene(SceneID nextSceneID, std::vector<SceneID> createSceneIDVector, std::vector<SceneID> deleteSceneIDVector)
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
			moveSceneData_.createSceneIDVector = std::move(createSceneIDVector);
			moveSceneData_.deleteSceneIDVector = std::move(deleteSceneIDVector);
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
				if (moveSceneData_.allowChangeMasterVolumeFadeOut)
				{
					audio::MusicPlayer::instance().setMasterVolume(
						1.f - (float)moveSceneData_.fadeLevel / moveSceneData_.moveSceneFrame
					);
				}
				if (moveSceneData_.fadeLevel == moveSceneData_.moveSceneFrame)
				{
					moveSceneData_.isFadeOut = false;
					if (!moveSceneData_.allowChangeMasterVolumeFadeIn)
					{
						audio::MusicPlayer::instance().setMasterVolume(1.f);
					}
					return true;
				}
			}
			else
			{
				--moveSceneData_.fadeLevel;
				if (moveSceneData_.allowChangeMasterVolumeFadeIn)
				{
					audio::MusicPlayer::instance().setMasterVolume(
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