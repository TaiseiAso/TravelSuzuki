#ifndef test_scene_h
#define test_scene_h

#include "base_scene.h"
#include "../graphic/image_manager.h"

namespace game::scene
{
	class TestScene : public BaseScene
	{
	private:
		mutable graphic::AnimeElapsedData testElapsedData_;

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
		TestScene(std::shared_ptr<SceneMediator>& sceneMediator);
		// �f�X�g���N�^
		~TestScene();
	};
}

#endif // !test_scene_h