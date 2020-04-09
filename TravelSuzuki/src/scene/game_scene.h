#ifndef game_scene_h
#define game_scene_h

#include "base_scene.h"

namespace game::scene
{
	class GameScene : public BaseScene
	{
	private:
		// 入力による変化
		void action() override;
		// ステップごとに進む処理
		void update() override;
		// 状態の描画
		void draw() const override;

	public:
		// コンストラクタ
		GameScene();
		// デストラクタ
		~GameScene();
	};
}

#endif // !game_scene_h