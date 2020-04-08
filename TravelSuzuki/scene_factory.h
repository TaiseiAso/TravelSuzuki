#ifndef scene_factory_h
#define scene_factory_h

#include <memory>
#include "scene_enum.h"
#include "title_scene.h"
#include "game_scene.h"
#include "result_scene.h"
#include "achievement_scene.h"

namespace game::scene
{
	class SceneFactory
	{
	public:
		std::unique_ptr<BaseScene> create(SceneID);
	};
}

#endif // !scene_factory_h