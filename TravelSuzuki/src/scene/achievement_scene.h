#ifndef achievement_scene_h
#define achievement_scene_h

#include "base_scene.h"

namespace game::scene
{
	class AchievementScene : public BaseScene
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
		AchievementScene(std::shared_ptr<SceneMediator>& sceneMediator);
		// デストラクタ
		~AchievementScene();
	};
}

#endif // !achievement_scene_h