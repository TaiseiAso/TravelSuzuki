#include "scene_mediator.h"
#include "DxLib.h"

namespace game::scene
{
	SceneMediator::SceneMediator()
	{
		moveSceneData_.isMovingScene = false;
	}

	SceneMediator::~SceneMediator() {}

	bool SceneMediator::isMovingScene() const
	{
		return moveSceneData_.isMovingScene;
	}

	SceneID SceneMediator::getNextSceneID()
	{
		if (moveSceneData_.isMovingScene) return moveSceneData_.nextSceneID;
		return SceneID::NONE;
	}

	std::vector<SceneID> SceneMediator::getCreateSceneIDVector()
	{
		if (moveSceneData_.isMovingScene) return moveSceneData_.createSceneIDVector;
		return {};
	}

	std::vector<SceneID> SceneMediator::getDeleteSceneIDVector()
	{
		if (moveSceneData_.isMovingScene) return moveSceneData_.deleteSceneIDVector;
		return {};
	}

	void SceneMediator::moveScene(SceneID nextSceneID, int moveFrame)
	{
		moveScene(nextSceneID, moveFrame, {}, {});
	}

	void SceneMediator::moveScene(SceneID nextSceneID, int moveFrame, std::vector<SceneID> createSceneIDVector, std::vector<SceneID> deleteSceneIDVector)
	{
		if (moveFrame >= 0)
		{
			moveSceneData_.createSceneIDVector.clear();
			moveSceneData_.createSceneIDVector.shrink_to_fit();
			moveSceneData_.deleteSceneIDVector.clear();
			moveSceneData_.deleteSceneIDVector.shrink_to_fit();

			moveSceneData_ = {
				true, nextSceneID, true, moveFrame, 0, createSceneIDVector, deleteSceneIDVector
			};
		}
	}

	bool SceneMediator::update()
	{
		if (isMovingScene())
		{
			if (moveSceneData_.moveFrame == 0)
			{
				moveSceneData_.isMovingScene = false;
				return true;
			}
			
			if (moveSceneData_.isFadeOut)
			{
				moveSceneData_.fadeLevel++;
				if (moveSceneData_.fadeLevel == moveSceneData_.moveFrame)
				{
					moveSceneData_.isFadeOut = false;
					return true;
				}
			}
			else
			{
				moveSceneData_.fadeLevel--;
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
		if (isMovingScene() && moveSceneData_.fadeLevel > 0 && moveSceneData_.moveFrame > 0)
		{
			int alpha = 255 * moveSceneData_.fadeLevel / moveSceneData_.moveFrame;
			if (alpha < 0) alpha = 0;
			else if (alpha > 255) alpha = 255;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			DrawBox(0, 0, 800, 640, GetColor(255, 255, 255), TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}
	}
}