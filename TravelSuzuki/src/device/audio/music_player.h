#ifndef music_player_h
#define music_player_h

#include <unordered_map>
#include "singleton/singleton.h"

namespace game::audio
{
	class MusicPlayer : public Singleton<MusicPlayer>
	{
		friend class Singleton<MusicPlayer>; // Singleton �ł̃C���X�^���X�쐬�͋���

	private:
		typedef struct {
			int handle; // �Đ����鉹�y�̃n���h��
			float volume; // ���y�̍Đ�����
			float distance; // �����ƃ��X�i�[�̋��� (0�ȉ��Ȃ狗���𖳎����ĉ��ʌ������Ȃ�)
		} MusicHandleAndVolume;

		typedef struct {
			int fadeFrame; // �t�F�[�h�ɂ�����t���[����
			float deltaVolumeFade; // 1�t���[���ŕω����鉹��
		} MusicVolumeFadeData;

		// �������ɓǂݍ��މ��y�̖��O�ƃt�@�C���p�X�̃}�b�v
		std::unordered_map<std::string, std::string> loadMusicNameToPath_;

		// �������ɓǂݍ��񂾉��y�̖��O�ƃn���h���̃}�b�v
		std::unordered_map<std::string, int> loadMusicNameToHandle_;

		// �Đ����Ă��鉹�y�̎��ʖ���<�������ꂽ�n���h��, �Đ�����>�̍\���̂̃}�b�v
		std::unordered_map<std::string, MusicHandleAndVolume> playMusicNameToHandleAndVolume_;

		// �Đ����Ă��鉹�y�̉��ʂ�ω������邽�߂̏��Z�b�g
		std::unordered_map<std::string, MusicVolumeFadeData> playMusicNameToVolumeFadeData_;

		// �S�̂̉��ʔ䗦 (-1����1�̊Ԃ̒l)
		float masterVolume_;

		// �����ƃ��X�i�[�̋����ɂ�鉹�ʌ����̌W�� (�傫���قǌ������ɂ���) (0�ȉ��Ȃ猸�����Ȃ�)
		float volumeAttenuationCoefficient_;

		// �Đ����̉��y�̉��ʂ�ύX����
		void setPlayMusicVolume(int playMusicHandle, float playMusicVolume, float playMusicDistance) const;
		// �Đ����̑S�Ẳ��y�̉��ʂ��X�V����
		void updateAllPlayMusicVolume() const;

		MusicPlayer(); // �O���ł̃C���X�^���X�쐬�͋֎~
		~MusicPlayer();

	public:
		// ���y�̖��O�ƃt�@�C���p�X���Ή��t����ꂽ�f�[�^�x�[�X��ǂݍ���
		void loadMusicNameToPathDatabase(std::string databaseFilePath, bool passFirstLine = true);
		
		// ���y���������ɓǂݍ��� (�f�[�^�x�[�X�̓ǂݍ��݂��O��)
		void loadMusic(const std::string& loadMusicName);
		// ���y���������ɓǂݍ���
		void loadMusic(const std::string& loadMusicName, const std::string& loadMusicFilePath);
		
		// ���y������������j������
		void deleteMusic(const std::string& loadMusicName);

		// �������ɓǂݍ��񂾉��y���Đ����� (���Ƃ��琧�䂵�Ȃ����ʉ��p)
		void playSE(const std::string& loadMusicName, float playMusicVolume, float playMusicDistance = 0.f) const;
		// �������ɓǂݍ��񂾉��y���Đ�����
		void playMusic(const std::string& loadMusicName, const std::string& playMusicName, float playMusicVolume, bool isLoop, bool topPositionFlag, float playMusicDistance = 0.f);

		// �Đ����̉��y���~����
		void stopMusic(const std::string& playMusicName);

		// ���ׂẲ��y������������j������
		void deleteAllMusic();

		// ���ׂĂ̍Đ����̉��y���~����
		void stopAllMusic();

		// �Đ����̉��y�̉��ʂ�ύX����
		void setPlayMusicVolume(const std::string& playMusicName, float playMusicVolume);
		// �Đ����̉��y�̃��X�i�[�Ƃ̋�����ύX����
		void setPlayMusicDistance(const std::string& playMusicName, float playMusicDistance);

		// �}�X�^�[���ʂ�ύX���� (-1����1�̊Ԃ̒l)
		void setMasterVolume(float masterVolume);
		// �}�X�^�[���ʂ��擾����
		float getMasterVolume() const;

		// �����ƃ��X�i�[�̋����ɂ�鉹�ʌ����̌W����ύX����
		void setVolumeAttenuationCoefficient(float volumeAttenuationCoefficient);
		// �����ƃ��X�i�[�̋����ɂ�鉹�ʌ����̌W�����擾����
		float getVolumeAttenuationCoefficient() const;

		/*
			��~���Ă���̂Ƀ������Ɏc���Ă��鉹�y�Ƃ��̃n���h��������������j������
			return: true->�j���ɐ���, false->�j�����Ȃ�����
		*/
		bool deleteStoppingMusic(const std::string& playMusicName);

		// �Đ����̉��y�̉��ʂ̃t�F�[�h���J�n����
		void startFadeMusicVolume(const std::string& playMusicName, float targetVolume, int fadeFrame);

		// �Đ����ł��t�F�[�h���̉��y�̉��ʂ��X�V����
		void updateFadeMusicVolume();
	};
}

#endif // !music_player_h