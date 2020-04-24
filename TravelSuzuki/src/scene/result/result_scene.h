#ifndef result_scene_h
#define result_scene_h

#include "scene/base_scene.h"

namespace game::scene::result
{
	class ResultScene : public BaseScene
	{
	private:
		// �V�[���̏���������
		void initialize() override;
		// �V�[���̏I������
		void finalize() override;

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