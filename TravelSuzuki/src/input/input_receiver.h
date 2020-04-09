#ifndef input_receiver_h
#define input_receiver_h

#include "../singleton/singleton.h"

namespace game::input
{
	class InputReceiver : public Singleton<InputReceiver>
	{
		friend class Singleton<InputReceiver>; // Singleton �ł̃C���X�^���X�쐬�͋���

	private:
		int pushKeyFrameArray_[256] = {}; // �S�ẴL�[��������Ă���t���[����

	public:
		// �L�[���͏�Ԃ��X�V����
		void update();
		// �w�肵���L�[��������Ă���t���[�������擾����
		int getPushKeyFrame(int keyID) const;

	protected:
		InputReceiver();// �O���ł̃C���X�^���X�쐬�͋֎~
		virtual ~InputReceiver();
	};
}

#endif // !input_receiver_h