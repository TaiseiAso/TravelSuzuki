#ifndef scene_manager_h
#define scene_manager_h

#include "scene_factory.h"

namespace game::scene
{
	class SceneManager
	{
	private:
		std::unique_ptr<SceneFactory> sceneFactory_; // �V�[���t�@�N�g��
		std::unique_ptr<BaseScene> currentScene_; // ���݂̃V�[��

		// ���͂ɂ��ω�
		void action();
		// �X�e�b�v���Ƃɐi�ޏ���
		void update();
		// ��Ԃ̕`��
		void draw() const;

	public:
		// �R���X�g���N�^
		SceneManager();
		// �f�X�g���N�^
		~SceneManager();

		// �X�e�b�v���Ƃ̏���
		void step();
	};
}

#endif // !scene_manager_h
