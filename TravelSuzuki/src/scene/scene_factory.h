#ifndef scene_factory_h
#define scene_factory_h

#include "test_scene.h"
#include "title_scene.h"
#include "game_scene.h"
#include "result_scene.h"
#include "achievement_scene.h"

namespace game::scene
{
	class SceneFactory
	{
	public:
		// �V�[���I�u�W�F�N�g���쐬����
		std::unique_ptr<BaseScene> createScene(SceneID sceneID, std::shared_ptr<SceneMediator>& sceneMediator);
	};
}

#endif // !scene_factory_h