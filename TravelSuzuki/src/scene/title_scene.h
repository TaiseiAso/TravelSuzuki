#ifndef title_scene_h
#define title_scene_h

#include "base_scene.h"

namespace game::scene
{
	class TitleScene : public BaseScene
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
		TitleScene();
		// �f�X�g���N�^
		~TitleScene();
	};
}

#endif // !title_scene_h