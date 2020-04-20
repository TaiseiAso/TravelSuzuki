#include "scene_factory.h"

namespace game::scene
{
	std::unique_ptr<BaseScene> SceneFactory::createScene(SceneID sceneID, const std::shared_ptr<SceneMediator>& sceneMediator)
	{
		std::unique_ptr<BaseScene> createdScene = nullptr;
		switch (sceneID)
		{
		case SceneID::TEST:
			createdScene = std::make_unique<test::TestScene>(sceneMediator);
			break;
		case SceneID::TITLE:
			createdScene = std::make_unique<title::TitleScene>(sceneMediator);
			break;
		case SceneID::BATTLE:
			createdScene = std::make_unique<battle::BattleScene>(sceneMediator);
			break;
		case SceneID::RESULT:
			createdScene = std::make_unique<result::ResultScene>(sceneMediator);
			break;
		case SceneID::ACHIEVEMENT:
			createdScene = std::make_unique<achievement::AchievementScene>(sceneMediator);
		}
		return createdScene;
	}
}