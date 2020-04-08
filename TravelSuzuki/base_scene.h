#ifndef base_scene_h
#define base_scene_h

#include "Dxlib.h"
//#include "SceneMover.h"

namespace game::scene
{
	class BaseScene
	{
	public:
		// コンストラクタ
		BaseScene();
		// デストラクタ
		virtual ~BaseScene();

		// 入力による変化
		virtual void action() = 0;
		// ステップごとに進む処理
		virtual void update() = 0;
		// 状態の描画
		virtual void draw() const = 0;
	};
}

#endif // ! base_scene_h