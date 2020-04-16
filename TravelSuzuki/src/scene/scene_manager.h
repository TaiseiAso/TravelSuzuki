#ifndef scene_manager_h
#define scene_manager_h

#include <unordered_map>
#include <memory>
#include "scene_enum.h"
#include "scene_mediator.h"
#include "title_scene.h"
#include "game_scene.h"
#include "result_scene.h"
#include "achievement_scene.h"

namespace game::scene
{
	class SceneManager
	{
	private:
		// シーン仲介者
		std::shared_ptr<SceneMediator> sceneMediator_;
		// シーンIDと作成したシーンのマップ
		std::unordered_map<SceneID, std::unique_ptr<BaseScene>> idToCreatedScene_;
		// 現在のシーンID
		SceneID currentSceneID_;

		// シーンを作成する
		void createScene(SceneID sceneID);
		// シーンを初期化する
		void initScene(SceneID sceneID);
		// シーンを終了する
		void finalScene(SceneID sceneID);
		// シーンを破棄する
		void deleteScene(SceneID sceneID);

		// シーン移動の処理
		void moveScene();

	public:
		// コンストラクタ
		SceneManager();
		// デストラクタ
		~SceneManager();

		// ステップごとの処理
		void step();
	};
}

#endif // !scene_manager_h