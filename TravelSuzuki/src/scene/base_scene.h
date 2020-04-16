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
		std::weak_ptr<SceneMediator> sceneMediator_;

	public:
		// コンストラクタ
		BaseScene(std::shared_ptr<SceneMediator>& sceneMediator);
		// デストラクタ
		virtual ~BaseScene();

		// シーンの初期化処理
		virtual void initialize() = 0;
		// シーンの終了処理
		virtual void finalize() = 0;

		// 入力による変化
		virtual void action() = 0;
		// ステップごとに進む処理
		virtual void update() = 0;
		// 状態の描画
		virtual void draw() const = 0;
	};
}

#endif // ! base_scene_h