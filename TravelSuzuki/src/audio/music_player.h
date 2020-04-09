#ifndef music_player_h
#define music_player_h

#include <unordered_map>
#include <string>
#include "../singleton/singleton.h"

namespace game::audio
{
	class MusicPlayer : public Singleton<MusicPlayer>
	{
		friend class Singleton<MusicPlayer>; // Singleton �ł̃C���X�^���X�쐬�͋���

	private:
		std::unordered_map<std::string, int> musicNameToID_; // ���y�̖��O�ƃn���h���̃}�b�v

	public:
		// ���y���������ɓǂݍ���
		void loadMusic(std::string musicName, std::string musicFilePath);
		// ���y������������j������
		void deleteMusic(std::string musicName);
		// �������ɓǂݍ��񂾉��y���Đ�����
		void playMusic(std::string musicName, bool isLoop, bool topPositionFlag);
		// �Đ����̉��y���~����
		void stopMusic(std::string musicName);

	protected:
		MusicPlayer() {} // �O���ł̃C���X�^���X�쐬�͋֎~
		virtual ~MusicPlayer();
	};
}

#endif // !music_player_h