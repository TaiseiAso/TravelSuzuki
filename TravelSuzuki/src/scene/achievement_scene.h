#ifndef achievement_scene_h
#define achievement_scene_h

#include "base_scene.h"

namespace game::scene
{
	class AchievementScene : public BaseScene
	{
	private:
		// 入力による変化
		void action() override;
		// ステップごとに進む処理
		void update() override;
		// 状態の描画
		void draw() override;

	public:
		// コンストラクタ
		AchievementScene();
		// デストラクタ
		~AchievementScene();
	};
}

#endif // !achievement_scene_h