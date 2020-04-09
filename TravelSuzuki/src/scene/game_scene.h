#ifndef game_scene_h
#define game_scene_h

#include "base_scene.h"

namespace game::scene
{
	class GameScene : public BaseScene
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
		GameScene();
		// �f�X�g���N�^
		~GameScene();
	};
}

#endif // !game_scene_h