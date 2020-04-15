#include "scene_mediator.h"
#include "../audio/music_player.h"
#include "DxLib.h"

namespace game::scene
{
	SceneMediator::SceneMediator()
	{
		moveSceneData_.isMovingScene = false;
		moveSceneData_.moveSceneFrame = 0;
		moveSceneData_.allowChangeMasterVolumeFadeOut = false;
		moveSceneData_.allowChangeMasterVolumeFadeIn = false;
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

	std::vector<SceneID> SceneMediator::getCreateSceneIDVector() const
	{
		return moveSceneData_.createSceneIDVector;
	}

	std::vector<SceneID> SceneMediator::getDeleteSceneIDVector() const
	{
		return moveSceneData_.deleteSceneIDVector;
	}

	float SceneMediator::getFadeRatio() const
	{
		if (!isMovingScene() || moveSceneData_.moveSceneFrame <= 0) return 0.f;
		float fadeRatio = (float)moveSceneData_.fadeLevel / moveSceneData_.moveSceneFrame;
		return moveSceneData_.isFadeOut ? fadeRatio : -fadeRatio;
	}

	void SceneMediator::setMoveSceneFrame(int moveSceneFrame)
	{
		if (!isMovingScene()) moveSceneData_.moveSceneFrame = moveSceneFrame;
	}

	void SceneMediator::setAllowChangeMasterVolumeFade(bool allowChangeMasterVolumeFadeOut, bool allowChangeMasterVolumeFadeIn)
	{
		if (!isMovingScene())
		{
			moveSceneData_.allowChangeMasterVolumeFadeOut = allowChangeMasterVolumeFadeOut;
			moveSceneData_.allowChangeMasterVolumeFadeIn = allowChangeMasterVolumeFadeIn;
		}
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

			moveSceneData_ = {
				true, nextSceneID, true, moveSceneData_.moveSceneFrame, 0, createSceneIDVector, deleteSceneIDVector,
				moveSceneData_.allowChangeMasterVolumeFadeOut, moveSceneData_.allowChangeMasterVolumeFadeIn
			};
		}
	}

	bool SceneMediator::updateMoveScene()
	{
		if (isMovingScene())
		{
			if (moveSceneData_.moveSceneFrame == 0)
			{
				moveSceneData_.isMovingScene = false;
				return true;
			}
			
			if (moveSceneData_.isFadeOut)
			{
				moveSceneData_.fadeLevel++;
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
				moveSceneData_.fadeLevel--;
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

	void SceneMediator::draw() const
	{
		if (isMovingScene() && moveSceneData_.fadeLevel > 0 && moveSceneData_.moveSceneFrame > 0)
		{
			int alpha = 255 * moveSceneData_.fadeLevel / moveSceneData_.moveSceneFrame;
			if (alpha < 0) alpha = 0;
			else if (alpha > 255) alpha = 255;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			DrawBox(0, 0, 800, 640, GetColor(255, 255, 255), TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}
	}
}