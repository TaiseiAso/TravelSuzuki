#ifndef fps_controller_h
#define fps_controller_h

#include "singleton/singleton.h"
#include "DxLib.h"

namespace game::fps
{
	class FPSController : public Singleton<FPSController>
	{
		friend class Singleton<FPSController>; // Singleton �ł̃C���X�^���X�쐬�͋���

	private:
		int startTime_; // ����J�n����
		int count_; // �J�E���^
		float fps_; // ���݂̐���FPS

		static const int N = 30; // FPS����̂��߂ɕ��ς����T���v����
		static const int FPS = 60; // �ݒ肵��FPS

		const unsigned int grayColor_ = GetColor(120, 120, 120); // �D�F

		FPSController(); // �O���ł̃C���X�^���X�쐬�͋֎~
		~FPSController();

	public:
		// �X�V
		void update();
		// �e�X�g�p��FPS�`��
		void draw() const;
		// FPS�Œ�̂��߈�莞�ԑҋ@
		void wait() const;
	};
}

#endif // !fps_controller_h
