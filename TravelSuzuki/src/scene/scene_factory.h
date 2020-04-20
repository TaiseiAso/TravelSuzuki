#ifndef scene_factory_h
#define scene_factory_h

#include "test_scene.h"
#include "title_scene.h"
#include "battle_scene.h"
#include "result_scene.h"
#include "achievement_scene.h"

namespace game::scene
{
	class SceneFactory
	{
	private:
		// コピーコンストラクタを禁止する
		SceneFactory(const SceneFactory&) = delete;
		SceneFactory(SceneFactory&&) = delete;

		// コピー代入演算子を禁止する
		SceneFactory& operator=(const SceneFactory&) = delete;
		SceneFactory& operator=(SceneFactory&&) = delete;

	public:
		SceneFactory() {}
		~SceneFactory() {}
		
		// シーンオブジェクトを作成する
		std::unique_ptr<BaseScene> createScene(SceneID sceneID, const std::shared_ptr<SceneMediator>& sceneMediator);
	};
}

#endif // !scene_factory_h