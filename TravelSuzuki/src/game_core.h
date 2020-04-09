#ifndef game_core_h
#define game_core_h

#include <memory>
#include "fps/fps_controller.h"
#include "scene/scene_manager.h"

namespace game
{
	// ゲームの最上階層クラス
	class GameCore
	{
	private:
		std::unique_ptr<fps::FPSController> fpsController_; // FPS固定
		std::unique_ptr<scene::SceneManager> sceneManager_; // シーン管理

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
