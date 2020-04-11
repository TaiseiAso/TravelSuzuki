#include <fstream>
#include <sstream>
#include "music_player.h"
#include "../utils/string_util.h"
#include "DxLib.h"

namespace game::audio
{
	void MusicPlayer::setPlayMusicVolume(int playMusicHandle, int volume)
	{
		int volumePal = (int)(masterVolume_ * volume);
		if (volumePal < 0) volumePal = 0;
		else if (volumePal > 255) volumePal = 255;
		ChangeVolumeSoundMem(volumePal, playMusicHandle);
	}

	void MusicPlayer::loadDatabase(std::string databaseFilePath, bool pathFirstLine)
	{
		loadMusicNameToPath_.clear();

		std::ifstream ifs(databaseFilePath);
		std::string line;
		if (pathFirstLine) std::getline(ifs, line); // àÍçsñ⁄ÇÕîÚÇŒÇ∑
		while (std::getline(ifs, line))
		{
			std::vector<std::string> strVec = StringUtil::split(line, ',');
			if (strVec.size() >= 2) loadMusicNameToPath_[strVec[0]] = strVec[1];
		}
	}

	void MusicPlayer::loadMusic(std::string loadMusicName)
	{
		auto itrLoad = loadMusicNameToPath_.find(loadMusicName);
		if (itrLoad != loadMusicNameToPath_.end())
		{
			loadMusic(loadMusicName, itrLoad->second);
		}
	}

	void MusicPlayer::loadMusic(std::string loadMusicName, std::string loadMusicFilePath)
	{
		auto itrLoad = loadMusicNameToHandle_.find(loadMusicName);
		if (itrLoad == loadMusicNameToHandle_.end())
		{
			loadMusicNameToHandle_[loadMusicName] = LoadSoundMem(loadMusicFilePath.c_str());
		}
	}

	void MusicPlayer::deleteMusic(std::string loadMusicName)
	{
		auto itrLoad = loadMusicNameToHandle_.find(loadMusicName);
		if (itrLoad != loadMusicNameToHandle_.end())
		{
			DeleteSoundMem(itrLoad->second);
			loadMusicNameToHandle_.erase(itrLoad);
		}
	}

	void MusicPlayer::playSE(std::string loadMusicName, int volume)
	{
		auto itrLoad = loadMusicNameToHandle_.find(loadMusicName);
		if (itrLoad != loadMusicNameToHandle_.end())
		{
			int playMusicHandle = DuplicateSoundMem(itrLoad->second);
			SetPlayFinishDeleteSoundMem(true, playMusicHandle);
			setPlayMusicVolume(playMusicHandle, volume);
			PlaySoundMem(playMusicHandle, DX_PLAYTYPE_BACK, false);
		}
	}

	void MusicPlayer::playSE(std::string loadMusicName, std::string playMusicName, int volume)
	{
		auto itrLoad = loadMusicNameToHandle_.find(loadMusicName);
		if (itrLoad != loadMusicNameToHandle_.end())
		{
			auto itrPlay = playMusicNameToHandle_.find(playMusicName);
			if (itrPlay == playMusicNameToHandle_.end())
			{
				playMusicNameToHandle_[playMusicName] = DuplicateSoundMem(itrLoad->second);
			}

			setPlayMusicVolume(playMusicNameToHandle_[playMusicName], volume);
			PlaySoundMem(playMusicNameToHandle_[playMusicName], DX_PLAYTYPE_BACK, false);
		}
	}

	void MusicPlayer::playMusic(std::string loadMusicName, std::string playMusicName, int volume, bool isLoop, bool topPositionFlag)
	{
		auto itrLoad = loadMusicNameToHandle_.find(loadMusicName);
		if (itrLoad != loadMusicNameToHandle_.end())
		{
			auto itrPlay = playMusicNameToHandle_.find(playMusicName);
			if (itrPlay == playMusicNameToHandle_.end())
			{
				playMusicNameToHandle_[playMusicName] = DuplicateSoundMem(itrLoad->second);
			}

			setPlayMusicVolume(playMusicNameToHandle_[playMusicName], volume);
			PlaySoundMem(
				playMusicNameToHandle_[playMusicName],
				isLoop ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK,
				topPositionFlag
			);
		}
	}

	void MusicPlayer::stopMusic(std::string playMusicName)
	{
		auto itrPlay = playMusicNameToHandle_.find(playMusicName);
		if (itrPlay != playMusicNameToHandle_.end())
		{
			StopSoundMem(itrPlay->second);
			DeleteSoundMem(itrPlay->second);
			playMusicNameToHandle_.erase(itrPlay);
		}
	}

	void MusicPlayer::deleteAllMusic()
	{
		InitSoundMem();
		loadMusicNameToHandle_.clear();
		playMusicNameToHandle_.clear();
	}

	void MusicPlayer::stopAllMusic()
	{
		for (auto itrPlay = playMusicNameToHandle_.begin(); itrPlay != playMusicNameToHandle_.end(); itrPlay++)
		{
			StopSoundMem(itrPlay->second);
			DeleteSoundMem(itrPlay->second);
		}
		playMusicNameToHandle_.clear();
	}

	void MusicPlayer::setPlayMusicVolume(std::string playMusicName, int volume)
	{
		auto itrPlay = playMusicNameToHandle_.find(playMusicName);
		if (itrPlay != playMusicNameToHandle_.end())
		{
			setPlayMusicVolume(itrPlay->second, volume);
		}
	}

	void MusicPlayer::setMasterVolume(float masterVolume)
	{
		float befMasterVolume = masterVolume_;
		masterVolume_ = masterVolume;
		for (auto itrPlay = playMusicNameToHandle_.begin(); itrPlay != playMusicNameToHandle_.end(); itrPlay++)
		{
			setPlayMusicVolume(itrPlay->second, (int)(GetVolumeSoundMem2(itrPlay->second) / befMasterVolume));
		}
	}

	bool MusicPlayer::deleteStoppingMusic(std::string playMusicName)
	{
		auto itrPlay = playMusicNameToHandle_.find(playMusicName);
		if (itrPlay != playMusicNameToHandle_.end())
		{
			if (CheckSoundMem(itrPlay->second) == 0)
			{
				DeleteSoundMem(itrPlay->second);
				playMusicNameToHandle_.erase(itrPlay);
				return true;
			}
		}
		return false;
	}

	MusicPlayer::MusicPlayer()
	{
		masterVolume_ = 1.f;
	}

	MusicPlayer::~MusicPlayer()
	{
		deleteAllMusic();
	}
}