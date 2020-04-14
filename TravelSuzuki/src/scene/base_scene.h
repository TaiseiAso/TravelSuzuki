#ifndef base_scene_h
#define base_scene_h

#include <memory>
#include "scene_mediator.h"

namespace game::scene
{
	class BaseScene
	{
	protected:
		// シーン仲介者
		std::shared_ptr<SceneMediator> sceneMediator_;

	public:
		// コンストラクタ
		BaseScene(std::shared_ptr<SceneMediator> sceneMediator);
		// デストラクタ
		virtual ~BaseScene();

		// シーンの初期化処理
		virtual void init() = 0;

		// 入力による変化
		virtual void action() = 0;
		// ステップごとに進む処理
		virtual void update() = 0;
		// 状態の描画
		virtual void draw() const = 0;
	};
}

#endif // ! base_scene_h