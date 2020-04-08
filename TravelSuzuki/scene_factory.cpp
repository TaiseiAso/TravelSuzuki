#include "scene_factory.h"

namespace game::scene
{
	std::unique_ptr<BaseScene> SceneFactory::create(SceneID sceneID)
	{
		std::unique_ptr<BaseScene> createdScene;
		switch (sceneID)
		{
		case SceneID::TITLE:
			createdScene.reset(new TitleScene());
			break;
		case SceneID::GAME:
			createdScene.reset(new GameScene());
			break;
		case SceneID::RESULT:
			createdScene.reset(new ResultScene());
			break;
		case SceneID::ACHIEVEMENT:
			createdScene.reset(new AchievementScene());
			break;
		default:
			return nullptr;
		}

		// シーンに共通の初期化処理

		return std::move(createdScene);
	}
}