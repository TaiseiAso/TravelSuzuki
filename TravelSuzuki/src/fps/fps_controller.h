#ifndef fps_controller_h
#define fps_controller_h

namespace game::fps
{
	class FPSController
	{
	private:
		int startTime_; // ����J�n����
		int count_; // �J�E���^
		float fps_; // ���݂̐���FPS
		static const int N = 30; // FPS����̂��߂ɕ��ς����T���v����
		static const int FPS = 60; // �ݒ肵��FPS

	public:
		// �R���X�g���N�^
		FPSController();
		// �f�X�g���N�^
		~FPSController();

		// �X�V
		void update();
		// �e�X�g�p��FPS�`��
		void draw() const;
		// FPS�Œ�̂��߈�莞�ԑҋ@
		void wait() const;
	};
}

#endif // !fps_controller_h
