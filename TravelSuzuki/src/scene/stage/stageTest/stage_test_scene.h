#ifndef stage_test_scene_h
#define stage_test_scene_h

#include "../stage_scene.h"

namespace game::scene::stage::stageTest
{
	class StageTestScene : public StageScene
	{
	private:
		// シーンの初期化処理
		void initialize() override;
		// シーンの終了処理
		void finalize() override;

	public:
		// コンストラクタ
		StageTestScene();
		// デストラクタ
		~StageTestScene();
	};
}

#endif // !stage_test_scene_h