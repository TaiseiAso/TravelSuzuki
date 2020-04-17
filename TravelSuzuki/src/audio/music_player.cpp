#include <fstream>
#include <sstream>
#include <algorithm>
#include "music_player.h"
#include "../utils/string_util.h"
#include "DxLib.h"

namespace game::audio
{
	void MusicPlayer::setPlayMusicVolume(int playMusicHandle, int playMusicVolume) const
	{
		int volumePal = static_cast<int>(masterVolume_ * fadeVolume_ * playMusicVolume);
		ChangeVolumeSoundMem(std::clamp<int>(volumePal, 0, 255), playMusicHandle);
	}

	void MusicPlayer::updateAllPlayMusicVolume() const
	{
		for (const auto& itrPlay : playMusicNameToHandleAndVolume_)
		{
			setPlayMusicVolume(itrPlay.second.handle, itrPlay.second.volume);
		}
	}

	void MusicPlayer::loadMusicNameToPathDatabase(std::string databaseFilePath, bool pathFirstLine)
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
			int loadMusicHandle = LoadSoundMem(loadMusicFilePath.c_str());
			if (loadMusicHandle != -1)
			{
				loadMusicNameToHandle_[loadMusicName] = loadMusicHandle;
			}
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

	void MusicPlayer::playSE(std::string loadMusicName, int playMusicVolume) const
	{
		auto itrLoad = loadMusicNameToHandle_.find(loadMusicName);
		if (itrLoad != loadMusicNameToHandle_.end())
		{
			int playMusicHandle = DuplicateSoundMem(itrLoad->second);
			if (playMusicHandle != -1)
			{
				SetPlayFinishDeleteSoundMem(TRUE, playMusicHandle);
				setPlayMusicVolume(playMusicHandle, playMusicVolume);
				PlaySoundMem(playMusicHandle, DX_PLAYTYPE_BACK, FALSE);
			}
		}
	}

	void MusicPlayer::playMusic(std::string loadMusicName, std::string playMusicName, int playMusicVolume, bool isLoop, bool topPositionFlag)
	{
		auto itrLoad = loadMusicNameToHandle_.find(loadMusicName);
		if (itrLoad != loadMusicNameToHandle_.end())
		{
			auto itrPlay = playMusicNameToHandleAndVolume_.find(playMusicName);
			if (itrPlay == playMusicNameToHandleAndVolume_.end())
			{
				int playMusicHandle = DuplicateSoundMem(itrLoad->second);
				if (playMusicHandle != -1)
				{
					playMusicNameToHandleAndVolume_[playMusicName] = MusicHandleAndVolume{ playMusicHandle, playMusicVolume };
					setPlayMusicVolume(playMusicHandle, playMusicVolume);
					PlaySoundMem(
						playMusicHandle,
						isLoop ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK,
						topPositionFlag
					);
				}
			}
		}
	}

	void MusicPlayer::stopMusic(std::string playMusicName)
	{
		auto itrPlay = playMusicNameToHandleAndVolume_.find(playMusicName);
		if (itrPlay != playMusicNameToHandleAndVolume_.end())
		{
			StopSoundMem(itrPlay->second.handle);
			DeleteSoundMem(itrPlay->second.handle);
			playMusicNameToHandleAndVolume_.erase(itrPlay);
		}
	}

	void MusicPlayer::deleteAllMusic()
	{
		InitSoundMem();
		loadMusicNameToHandle_.clear();
		playMusicNameToHandleAndVolume_.clear();
	}

	void MusicPlayer::stopAllMusic()
	{
		for (const auto& itrPlay : playMusicNameToHandleAndVolume_)
		{
			StopSoundMem(itrPlay.second.handle);
			DeleteSoundMem(itrPlay.second.handle);
		}
		playMusicNameToHandleAndVolume_.clear();
	}

	void MusicPlayer::setPlayMusicVolume(std::string playMusicName, int playMusicVolume)
	{
		auto itrPlay = playMusicNameToHandleAndVolume_.find(playMusicName);
		if (itrPlay != playMusicNameToHandleAndVolume_.end())
		{
			itrPlay->second.volume = playMusicVolume;
			setPlayMusicVolume(itrPlay->second.handle, playMusicVolume);
		}
	}

	void MusicPlayer::setMasterVolume(float masterVolume)
	{
		masterVolume_ = masterVolume;
		updateAllPlayMusicVolume();
	}

	void MusicPlayer::setFadeVolume(float fadeVolume)
	{
		fadeVolume_ = fadeVolume;
		updateAllPlayMusicVolume();
	}
	
	bool MusicPlayer::deleteStoppingMusic(std::string playMusicName)
	{
		auto itrPlay = playMusicNameToHandleAndVolume_.find(playMusicName);
		if (itrPlay != playMusicNameToHandleAndVolume_.end())
		{
			if (CheckSoundMem(itrPlay->second.handle) == 0)
			{
				DeleteSoundMem(itrPlay->second.handle);
				playMusicNameToHandleAndVolume_.erase(itrPlay);
				return true;
			}
		}
		return false;
	}

	MusicPlayer::MusicPlayer()
		: masterVolume_(1.f),
		  fadeVolume_(1.f)
	{}

	MusicPlayer::~MusicPlayer()
	{
		deleteAllMusic();
	}
}