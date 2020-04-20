#ifndef game_core_h
#define game_core_h

#include <memory>
#include "scene/scene_manager.h"

namespace game
{
	// ゲームの最上階層クラス
	class GameCore
	{
	private:
		std::unique_ptr<scene::SceneManager> sceneManager_; // シーン管理

		// コピーコンストラクタを禁止する
		GameCore(const GameCore&) = delete;
		GameCore(GameCore&&) = delete;

		// コピー代入演算子を禁止する
		GameCore& operator=(const GameCore&) = delete;
		GameCore& operator=(GameCore&&) = delete;

	public:
		// コンストラクタ
		GameCore();
		// デストラクタ
		~GameCore();

		// ゲームのメインループ
		void loop();
	};
}

#endif // !game_core_h
