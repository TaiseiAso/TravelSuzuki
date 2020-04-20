#ifndef scene_manager_h
#define scene_manager_h

#include <unordered_map>
#include "scene_factory.h"

namespace game::scene
{
	class SceneManager
	{
	private:
		// シーン仲介者
		std::shared_ptr<SceneMediator> sceneMediator_;
		
		// シーンファクトリ
		SceneFactory sceneFactory_;

		// シーンIDと作成したシーンのマップ
		std::unordered_map<SceneID, std::unique_ptr<BaseScene>> idToCreatedScene_;
		// 現在のシーンID
		SceneID currentSceneID_;

		// コピーコンストラクタを禁止する
		SceneManager(const SceneManager&) = delete;
		SceneManager(SceneManager&&) = delete;

		// コピー代入演算子を禁止する
		SceneManager& operator=(const SceneManager&) = delete;
		SceneManager& operator=(SceneManager&&) = delete;

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

		// ステップごとの処理 (終了時falseを返す)
		bool step();
	};
}

#endif // !scene_manager_h