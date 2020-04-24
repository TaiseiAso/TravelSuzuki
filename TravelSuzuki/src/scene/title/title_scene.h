#ifndef title_scene_h
#define title_scene_h

#include "scene/base_scene.h"
#include "DxLib.h"

namespace game::scene::title
{
	class TitleScene : public BaseScene
	{
	private:
		// �^�C�g����ʐ�p //////////////////////////////////////
		// << �񋓌^ >>
		enum class Mode
		{
			FIRST,
			MENU
		};

		// << �萔 >>
		const unsigned int whiteColor_ = GetColor(255, 255, 255); // ���F
		const unsigned int blackColor_ = GetColor(0, 0, 0); // ���F
		const unsigned int blueColor_ = GetColor(80, 60, 240); // �F
		const unsigned int greenColor_ = GetColor(60, 200, 80);  // �ΐF
		const unsigned int redColor_ = GetColor(200, 60, 80);  // �ԐF

		// << �ϐ� >>
		int elapsedFrame_; // �o�߃t���[����
		Mode mode_; // ��ʏ�
		int cursor_; // �J�[�\���ʒu

		// << ����֘A >>
		void actionPleasePressSpaceKey(); // �Q�[���J�n����̑���
		void actionMenu(); // ���j���[��ʂ̑���

		// << �`��֘A >>
		void drawBackGround() const; // �w�i�`��
		void drawTitleLogo() const; // �^�C�g�����S�`��
		void drawPleasePressSpaceKey() const; // �u�X�y�[�X�L�[�������Ă��������v���b�Z�[�W�`��
		void drawMenu() const; // ���j���[�`��
		//////////////////////////////////////////////////////////

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
		TitleScene();
		// �f�X�g���N�^
		~TitleScene();
	};
}

#endif // !title_scene_h