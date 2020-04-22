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
		typedef struct {
			int handle; // 再生する音楽のハンドル
			int volume; // 音楽の再生音量
		} MusicHandleAndVolume;

		// メモリに読み込む音楽の名前とファイルパスのマップ
		std::unordered_map<std::string, std::string> loadMusicNameToPath_;

		// メモリに読み込んだ音楽の名前とハンドルのマップ
		std::unordered_map<std::string, int> loadMusicNameToHandle_;

		// 再生している音楽の識別名と<複製されたハンドル, 再生音量>の構造体のマップ
		std::unordered_map<std::string, MusicHandleAndVolume> playMusicNameToHandleAndVolume_;

		// 全体の音量比率
		float masterVolume_;
		// 主にフェードインアウト中の音量比率
		float fadeVolume_;

		// 再生中の音楽の音量を変更する
		void setPlayMusicVolume(int playMusicHandle, int playMusicVolume) const;
		// 再生中の全ての音楽の音量を更新する
		void updateAllPlayMusicVolume() const;

		MusicPlayer(); // 外部でのインスタンス作成は禁止
		~MusicPlayer();

	public:
		// 音楽の名前とファイルパスが対応付けられたデータベースを読み込む
		void loadMusicNameToPathDatabase(std::string databaseFilePath, bool pathFirstLine = true);
		
		// 音楽をメモリに読み込む
		void loadMusic(std::string loadMusicName);
		void loadMusic(std::string loadMusicName, std::string loadMusicFilePath);
		
		// 音楽をメモリから破棄する
		void deleteMusic(std::string loadMusicName);

		// メモリに読み込んだ音楽を再生する
		void playSE(std::string loadMusicName, int playMusicVolume) const;
		void playMusic(std::string loadMusicName, std::string playMusicName, int playMusicVolume, bool isLoop = false, bool topPositionFlag = false);

		// 再生中の音楽を停止する
		void stopMusic(std::string playMusicName);

		// すべての音楽をメモリから破棄する
		void deleteAllMusic();

		// すべての再生中の音楽を停止する
		void stopAllMusic();

		// 再生中の音楽の音量を変更する
		void setPlayMusicVolume(std::string playMusicName, int playMusicVolume);

		// マスター音量を変更する
		void setMasterVolume(float masterVolume);
		// フェード音量を変更する
		void setFadeVolume(float fadeVolume);

		/*
			停止しているのにメモリに残っている音楽とそのハンドルをメモリから破棄する
			return: true->破棄に成功, false->破棄しなかった
		*/
		bool deleteStoppingMusic(std::string playMusicName);
	};
}

#endif // !music_player_h