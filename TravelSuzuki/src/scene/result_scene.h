#ifndef result_scene_h
#define result_scene_h

#include "base_scene.h"

namespace game::scene
{
	class ResultScene : public BaseScene
	{
	private:
		// シーンの初期化処理
		void init() override;

		// 入力による変化
		void action() override;
		// ステップごとに進む処理
		void update() override;
		// 状態の描画
		void draw() const override;

	public:
		// コンストラクタ
		ResultScene(std::shared_ptr<SceneMediator> sceneMediator);
		// デストラクタ
		~ResultScene();
	};
}

#endif // !result_scene_h