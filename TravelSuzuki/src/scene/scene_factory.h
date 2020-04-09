#ifndef scene_factory_h
#define scene_factory_h

#include <memory>
#include "scene_enum.h"
#include "base_scene.h"

namespace game::scene
{
	class SceneFactory
	{
	public:
		std::unique_ptr<BaseScene> create(SceneID sceneID);
	};
}

#endif // !scene_factory_h