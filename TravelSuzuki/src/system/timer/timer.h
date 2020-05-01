#ifndef timer_h
#define timer_h

#include "DxLib.h"

namespace game::timer
{
	class Timer
	{
	private:
		const unsigned int whiteColor_ = GetColor(255, 255, 255); // ���F
		const unsigned int redColor_ = GetColor(255, 60, 60); // �ԐF

		int x_; // �����X���W
		int y_; // �E���Y���W
		float remainTime_; // �c�莞��
		bool isFinished_; // ���Ԑ����t���O
		bool isStop_; // �ꎞ��~�t���O

		int fontHandle_; // �t�H���g�̃n���h��

		// �R�s�[�R���X�g���N�^���֎~����
		Timer(const Timer&) = delete;
		Timer(Timer&&) = delete;

		// �R�s�[������Z�q���֎~����
		Timer& operator=(const Timer&) = delete;
		Timer& operator=(Timer&&) = delete;

	public:
		// �R���X�g���N�^
		Timer(int x, int y, int fontSize);
		// �f�X�g���N�^
		~Timer();

		// �X�e�b�v���Ƃɐi�ޏ���
		void update();
		// ��Ԃ̕`��
		void draw() const;

		// �c�莞�Ԃ��擾����
		float getRemainTime() const;
		// ���Ԑ����ɂȂ��������擾����
		bool isFinished() const;
		// �ꎞ��~���Ă��邩���擾����
		bool isStop() const;

		// �c�莞�Ԃ�ݒ肷��
		void setRemainTime(float remainTime);
		// �ꎞ��~����
		void stop();
		// �ꎞ��~����������
		void resume();

	};
}

#endif // !timer_h