#include "scene_factory.h"

namespace game::scene
{
	std::unique_ptr<BaseScene> SceneFactory::createScene(SceneID sceneID, std::shared_ptr<SceneMediator>& sceneMediator)
	{
		std::unique_ptr<BaseScene> createdScene = nullptr;
		switch (sceneID)
		{
		case SceneID::TEST:
			createdScene = std::make_unique<TestScene>(sceneMediator);
			break;
		case SceneID::TITLE:
			createdScene = std::make_unique<TitleScene>(sceneMediator);
			break;
		case SceneID::GAME:
			createdScene = std::make_unique<GameScene>(sceneMediator);
			break;
		case SceneID::RESULT:
			createdScene = std::make_unique<ResultScene>(sceneMediator);
			break;
		case SceneID::ACHIEVEMENT:
			createdScene = std::make_unique<AchievementScene>(sceneMediator);
		}
		return createdScene;
	}
}