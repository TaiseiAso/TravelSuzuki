#include "music_player.h"
#include "DxLib.h"

namespace game::audio
{
	void MusicPlayer::loadMusic(std::string musicName, std::string musicFilePath)
	{
		auto itr = musicNameToID_.find(musicName);
		if (itr == musicNameToID_.end())
		{
			int handle = LoadSoundMem(musicFilePath.c_str());
			musicNameToID_[musicName] = handle;
		}
	}

	void MusicPlayer::deleteMusic(std::string musicName)
	{
		auto itr = musicNameToID_.find(musicName);
		if (itr != musicNameToID_.end())
		{
			DeleteSoundMem(itr->second);
			musicNameToID_.erase(itr);
		}
	}

	void MusicPlayer::playMusic(std::string musicName, bool isLoop, bool topPositionFlag = true)
	{
		auto itr = musicNameToID_.find(musicName);
		if (itr != musicNameToID_.end())
		{
			PlaySoundMem(
				itr->second,
				isLoop ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK,
				topPositionFlag
			);
		}
	}

	void MusicPlayer::stopMusic(std::string musicName)
	{
		auto itr = musicNameToID_.find(musicName);
		if (itr != musicNameToID_.end())
		{
			StopSoundMem(itr->second);
		}
	}

	MusicPlayer::~MusicPlayer()
	{
		InitSoundMem();
	}
}