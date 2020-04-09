#ifndef result_scene_h
#define result_scene_h

#include "base_scene.h"

namespace game::scene
{
	class ResultScene : public BaseScene
	{
	private:
		// ���͂ɂ��ω�
		void action() override;
		// �X�e�b�v���Ƃɐi�ޏ���
		void update() override;
		// ��Ԃ̕`��
		void draw() const override;

	public:
		// �R���X�g���N�^
		ResultScene();
		// �f�X�g���N�^
		~ResultScene();
	};
}

#endif // !result_scene_h