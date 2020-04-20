#ifndef test_scene_h
#define test_scene_h

#include "base_scene.h"
#include "../graphic/image_manager.h"

namespace game::scene::test
{
	class TestScene : public BaseScene
	{
	private:
		mutable graphic::AnimeElapsedData testElapsedData_;

		// シーンの初期化処理
		void initialize() override;
		// シーンの終了処理
		void finalize() override;

		// 入力による変化
		void action() override;
		// ステップごとに進む処理
		void update() override;
		// 状態の描画
		void draw() const override;

	public:
		// コンストラクタ
		TestScene(const std::shared_ptr<SceneMediator>& sceneMediator);
		// デストラクタ
		~TestScene();
	};
}

#endif // !test_scene_h