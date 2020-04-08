#ifndef scene_manager_h
#define scene_manager_h

//#include "SceneMover.h"
#include "scene_factory.h"

namespace game::scene
{
	class SceneManager
	{
	private:
		std::unique_ptr<SceneFactory> sceneFactory_; // シーンファクトリ
		std::unique_ptr<BaseScene> currentScene_; // 現在のシーン

		// 入力による変化
		void action();
		// ステップごとに進む処理
		void update();
		// 状態の描画
		void draw() const;

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

