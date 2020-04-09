#ifndef game_core_h
#define game_core_h

#include <memory>
#include "fps/fps_controller.h"
#include "scene/scene_manager.h"

namespace game
{
	// �Q�[���̍ŏ�K�w�N���X
	class GameCore
	{
	private:
		std::unique_ptr<fps::FPSController> fpsController_; // FPS�Œ�
		std::unique_ptr<scene::SceneManager> sceneManager_; // �V�[���Ǘ�

	public:
		// �R���X�g���N�^
		GameCore();
		// �f�X�g���N�^
		~GameCore();

		// �Q�[���̃��C�����[�v
		void loop();
	};
}

#endif // !game_core_h