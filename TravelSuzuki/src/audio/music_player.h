#ifndef music_player_h
#define music_player_h

#include <unordered_map>
#include "../singleton/singleton.h"

namespace game::audio
{
	class MusicPlayer : public Singleton<MusicPlayer>
	{
		friend class Singleton<MusicPlayer>; // Singleton でのインスタンス作成は許可

	private:
		// メモリに読み込んだ音楽の名前とファイルパスのマップ
		std::unordered_map<std::string, std::string> loadMusicNameToPath_;

		// メモリに読み込んだ音楽の名前とハンドルのマップ
		std::unordered_map<std::string, int> loadMusicNameToHandle_;

		// 再生している音楽の識別名と複製されたハンドルのマップ
		std::unordered_map<std::string, int> playMusicNameToHandle_;

		// 全体の音量比率
		float masterVolume_;

		// 再生中の音楽の音量を変更する
		void setPlayMusicVolume(int playMusicHandle, int volume);

	public:
		// 音楽の名前とファイルパスが対応付けられたデータベースを読み込む
		void loadDatabase(std::string databaseFilePath, bool pathFirstLine = true);
		
		// 音楽をメモリに読み込む
		void loadMusic(std::string loadMusicName);
		void loadMusic(std::string loadMusicName, std::string loadMusicFilePath);
		
		// 音楽をメモリから破棄する
		void deleteMusic(std::string loadMusicName);

		// メモリに読み込んだ音楽を再生する
		void playSE(std::string loadMusicName, int volume);
		void playSE(std::string loadMusicName, std::string playMusicName, int volume);
		void playMusic(std::string loadMusicName, std::string playMusicName, int volume, bool isLoop, bool topPositionFlag);

		// 再生中の音楽を停止する
		void stopMusic(std::string playMusicName);

		// すべての音楽をメモリから破棄する
		void deleteAllMusic();

		// すべての再生中の音楽を停止する
		void stopAllMusic();

		// 再生中の音楽の音量を変更する
		void setPlayMusicVolume(std::string playMusicName, int volume);

		// マスター音量を変更する
		void setMasterVolume(float masterVolume);

		/*
			停止しているのにメモリに残っている音楽とそのハンドルをメモリから破棄する
			return: true->破棄に成功, false->破棄しなかった
		*/
		bool deleteStoppingMusic(std::string playMusicName);

	protected:
		MusicPlayer(); // 外部でのインスタンス作成は禁止
		virtual ~MusicPlayer();
	};
}

#endif // !music_player_h