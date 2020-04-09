#ifndef achievement_scene_h
#define achievement_scene_h

#include "base_scene.h"

namespace game::scene
{
	class AchievementScene : public BaseScene
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
		AchievementScene();
		// �f�X�g���N�^
		~AchievementScene();
	};
}

#endif // !achievement_scene_h