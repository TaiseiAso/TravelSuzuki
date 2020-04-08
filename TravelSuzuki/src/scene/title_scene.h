#ifndef title_scene_h
#define title_scene_h

#include "base_scene.h"

namespace game::scene
{
	class TitleScene : public BaseScene
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
		TitleScene();
		// デストラクタ
		~TitleScene();
	};
}

#endif // !title_scene_h