#ifndef base_scene_h
#define base_scene_h

namespace game::scene
{
	class BaseScene
	{
	public:
		// �R���X�g���N�^
		BaseScene();
		// �f�X�g���N�^
		virtual ~BaseScene();

		// ���͂ɂ��ω�
		virtual void action() = 0;
		// �X�e�b�v���Ƃɐi�ޏ���
		virtual void update() = 0;
		// ��Ԃ̕`��
		virtual void draw() const = 0;
	};
}

#endif // ! base_scene_h