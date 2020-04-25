#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include "music_player.h"
#include "utils/string_util.h"
#include "DxLib.h"

namespace game::audio
{
	void MusicPlayer::setPlayMusicVolume(int playMusicHandle, float playMusicVolume, float playMusicDistance) const
	{
		float volume
			= (volumeAttenuationCoefficient_ > 0.f && playMusicDistance > 0.f)
			? playMusicVolume / std::powf(playMusicDistance * volumeAttenuationCoefficient_ + 1.f, 2.f)
			: playMusicVolume;
		int volumePal = static_cast<int>(std::roundf(masterVolume_ * volume));
		ChangeVolumeSoundMem(std::clamp<int>(volumePal, 0, 255), playMusicHandle);
	}

	void MusicPlayer::updateAllPlayMusicVolume() const
	{
		for (const auto& itrPlay : playMusicNameToHandleAndVolume_)
		{
			setPlayMusicVolume(itrPlay.second.handle, itrPlay.second.volume, itrPlay.second.distance);
		}
	}

	MusicPlayer::MusicPlayer()
		: masterVolume_(1.f),
		  volumeAttenuationCoefficient_(-1.f)
	{}

	MusicPlayer::~MusicPlayer()
	{
		deleteAllMusic();
	}

	void MusicPlayer::loadMusicNameToPathDatabase(std::string databaseFilePath, bool passFirstLine)
	{
		loadMusicNameToPath_.clear();

		std::ifstream ifs(databaseFilePath);
		std::string line;
		if (passFirstLine) std::getline(ifs, line); // àÍçsñ⁄ÇÕîÚÇŒÇ∑
		while (std::getline(ifs, line))
		{
			std::vector<std::string> strVec = stringUtil::split(line, ',');
			if (strVec.size() >= 2) loadMusicNameToPath_[strVec[0]] = strVec[1];
		}
	}

	void MusicPlayer::loadMusic(const std::string& loadMusicName)
	{
		auto itrLoad = loadMusicNameToPath_.find(loadMusicName);
		if (itrLoad != loadMusicNameToPath_.end())
		{
			loadMusic(loadMusicName, itrLoad->second);
		}
	}

	void MusicPlayer::loadMusic(const std::string& loadMusicName, const std::string& loadMusicFilePath)
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

	void MusicPlayer::deleteMusic(const std::string& loadMusicName)
	{
		auto itrLoad = loadMusicNameToHandle_.find(loadMusicName);
		if (itrLoad != loadMusicNameToHandle_.end())
		{
			DeleteSoundMem(itrLoad->second);
			loadMusicNameToHandle_.erase(itrLoad);
		}
	}

	void MusicPlayer::playSE(const std::string& loadMusicName, float playMusicVolume, float playMusicDistance) const
	{
		auto itrLoad = loadMusicNameToHandle_.find(loadMusicName);
		if (itrLoad != loadMusicNameToHandle_.end())
		{
			int playMusicHandle = DuplicateSoundMem(itrLoad->second);
			if (playMusicHandle != -1)
			{
				SetPlayFinishDeleteSoundMem(TRUE, playMusicHandle);
				setPlayMusicVolume(playMusicHandle, playMusicVolume, playMusicDistance);
				PlaySoundMem(playMusicHandle, DX_PLAYTYPE_BACK, FALSE);
			}
		}
	}

	void MusicPlayer::playMusic(const std::string& loadMusicName, const std::string& playMusicName, float playMusicVolume, bool isLoop, bool topPositionFlag, float playMusicDistance)
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
					playMusicNameToHandleAndVolume_[playMusicName] = MusicHandleAndVolume{ playMusicHandle, playMusicVolume, playMusicDistance };
					setPlayMusicVolume(playMusicHandle, playMusicVolume, playMusicDistance);
					PlaySoundMem(
						playMusicHandle,
						isLoop ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK,
						topPositionFlag
					);
				}
			}
		}
	}

	void MusicPlayer::stopMusic(const std::string& playMusicName)
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

	void MusicPlayer::setPlayMusicVolume(const std::string& playMusicName, float playMusicVolume)
	{
		auto itrPlay = playMusicNameToHandleAndVolume_.find(playMusicName);
		if (itrPlay != playMusicNameToHandleAndVolume_.end())
		{
			itrPlay->second.volume = playMusicVolume;
			setPlayMusicVolume(itrPlay->second.handle, playMusicVolume, itrPlay->second.distance);
		}
	}

	void MusicPlayer::setPlayMusicDistance(const std::string& playMusicName, float playMusicDistance)
	{
		auto itrPlay = playMusicNameToHandleAndVolume_.find(playMusicName);
		if (itrPlay != playMusicNameToHandleAndVolume_.end())
		{
			itrPlay->second.distance = playMusicDistance;
			setPlayMusicVolume(itrPlay->second.handle, itrPlay->second.volume, playMusicDistance);
		}
	}

	void MusicPlayer::setMasterVolume(float masterVolume)
	{
		masterVolume_ = std::clamp<float>(masterVolume, 0.f, 1.f);
		updateAllPlayMusicVolume();
	}

	float MusicPlayer::getMasterVolume() const
	{
		return masterVolume_;
	}

	void MusicPlayer::setVolumeAttenuationCoefficient(float volumeAttenuationCoefficient)
	{
		volumeAttenuationCoefficient_ = volumeAttenuationCoefficient;
		updateAllPlayMusicVolume();
	}

	float MusicPlayer::getVolumeAttenuationCoefficient() const
	{
		return volumeAttenuationCoefficient_;
	}
	
	bool MusicPlayer::deleteStoppingMusic(const std::string& playMusicName)
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

	void MusicPlayer::startFadeMusicVolume(const std::string& playMusicName, float targetVolume, int fadeFrame, bool stopWhenFadeEnd)
	{
		auto itrPlay = playMusicNameToHandleAndVolume_.find(playMusicName);
		if (itrPlay != playMusicNameToHandleAndVolume_.end())
		{
			playMusicNameToVolumeFadeData_[playMusicName] = 
			{
				fadeFrame,
				(targetVolume - itrPlay->second.volume) / fadeFrame,
				stopWhenFadeEnd
			};
		}
	}

	void MusicPlayer::updateFadeMusicVolume()
	{
		for (auto itrFade = playMusicNameToVolumeFadeData_.begin(); itrFade != playMusicNameToVolumeFadeData_.end();)
		{
			auto itrPlay = playMusicNameToHandleAndVolume_.find(itrFade->first);
			if (itrPlay != playMusicNameToHandleAndVolume_.end())
			{
				itrPlay->second.volume += itrFade->second.deltaVolumeFade;
				setPlayMusicVolume(itrPlay->second.handle, itrPlay->second.volume, itrPlay->second.distance);

				if (--itrFade->second.fadeFrame == 0)
				{
					if (itrFade->second.stopWhenFadeEnd)
					{
						StopSoundMem(itrPlay->second.handle);
						DeleteSoundMem(itrPlay->second.handle);
						playMusicNameToHandleAndVolume_.erase(itrPlay);
					}
					itrFade = playMusicNameToVolumeFadeData_.erase(itrFade);
				}
				else ++itrFade;
			}
			else
			{
				itrFade = playMusicNameToVolumeFadeData_.erase(itrFade);
			}
		}
	}
}