#ifndef stage_test_scene_h
#define stage_test_scene_h

#include "../stage_scene.h"

namespace game::scene::stage::stageTest
{
	class StageTestScene : public StageScene
	{
	private:
		// �V�[���̏���������
		void initialize() override;
		// �V�[���̏I������
		void finalize() override;

	public:
		// �R���X�g���N�^
		StageTestScene();
		// �f�X�g���N�^
		~StageTestScene();
	};
}

#endif // !stage_test_scene_h