#ifndef music_player_h
#define music_player_h

#include <unordered_map>
#include <string>
#include "../singleton/singleton.h"

namespace game::audio
{
	class MusicPlayer : public Singleton<MusicPlayer>
	{
		friend class Singleton<MusicPlayer>; // Singleton でのインスタンス作成は許可

	private:
		std::unordered_map<std::string, int> musicNameToID_; // 音楽の名前とハンドルのマップ

	public:
		// 音楽をメモリに読み込む
		void loadMusic(std::string musicName, std::string musicFilePath);
		// 音楽をメモリから破棄する
		void deleteMusic(std::string musicName);
		// メモリに読み込んだ音楽を再生する
		void playMusic(std::string musicName, bool isLoop, bool topPositionFlag);
		// 再生中の音楽を停止する
		void stopMusic(std::string musicName);

	protected:
		MusicPlayer() {} // 外部でのインスタンス作成は禁止
		virtual ~MusicPlayer();
	};
}

#endif // !music_player_h