#ifndef battle_scene_h
#define battle_scene_h

#include "base_scene.h"

namespace game::scene::battle
{
	class BattleScene : public BaseScene
	{
	private:
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
		BattleScene(const std::shared_ptr<SceneMediator>& sceneMediator);
		// デストラクタ
		~BattleScene();
	};
}

#endif // !battle_scene_h