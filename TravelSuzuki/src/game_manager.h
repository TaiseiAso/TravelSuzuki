#ifndef game_manager_h
#define game_manager_h

#include "pattern/singleton.h"
#include "system/timer/timer.h"
#include "DxLib.h"

namespace game
{
	class GameManager : public Singleton<GameManager>
	{
		friend class Singleton<GameManager>; // Singleton �ł̃C���X�^���X�쐬�͋���

	private:
		const unsigned int blackColor_ = GetColor(0, 0, 0); // ���F

		// ���Ԑ������Ǘ�����^�C�}�[
		std::unique_ptr<timer::Timer> timer_;

		GameManager(); // �O���ł̃C���X�^���X�쐬�͋֎~
		~GameManager();

	public:
		// ���͂ɂ��ω�
		void action();
		// �X�e�b�v���Ƃɐi�ޏ���
		void update();
		// ��Ԃ̕`��
		void draw() const;

		// �^�C�}�[�ւ̎Q�Ƃ�Ԃ�
		timer::Timer& getTimerRef();
	};
}

#endif // !game_manager_h