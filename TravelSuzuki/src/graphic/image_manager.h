#ifndef image_manager_h
#define image_manager_h

#include <unordered_map>
#include "../singleton/singleton.h"

namespace game::graphic
{
	typedef struct {
		int frame; // ある画像における経過フレーム数
		int sheet; // アニメの表示画像番号
	} AnimeElapsedData;

	class ImageManager : public Singleton<ImageManager>
	{
		friend class Singleton<ImageManager>; // Singleton でのインスタンス作成は許可

	private:
		typedef struct {
			int allNum; // 画像の分割総数
			int xNum; // 画像の横に対する分割数
			int yNum; // 画像の縦に対する分割数
			int sizeX; // 分割後の画像の横のサイズ
			int sizeY; // 分割後の画像の縦のサイズ
		} ImageDivData;

		// メモリに読み込む画像の名前とファイルパスのマップ
		std::unordered_map<std::string, std::string> imageNameToPath_;
		// メモリに読み込む集合画像の名前と画像の分割方法の構造体のマップ
		std::unordered_map<std::string, ImageDivData> groupNameToDivData_;
		// メモリに読み込む集合画像の名前と分割後の画像の描画フレーム数のリストのマップ
		std::unordered_map<std::string, std::vector<int>> groupNameToFrameVector_;
		
		// メモリに読み込んだ画像の名前とハンドルのマップ
		std::unordered_map<std::string, int> imageNameToHandle_;
		// メモリに読み込んだ集合画像の名前とハンドルのリストのマップ
		std::unordered_map<std::string, std::vector<int>> groupNameToHandleVector_;

	public:
		// 画像(集合画像を含む)の名前とファイルパスが対応付けられたデータベースを読み込む
		void loadImageNameToPathDatabase(std::string databaseFilePath, bool passFirstLine = true);
		// 集合画像の名前と画像の分割方法が対応付けられたデータベースを読み込む
		void loadGroupNameToDivDataDatabase(std::string databaseFilePath, bool passFirstLine = true);
		// 集合画像の名前と分割後の画像の描画フレーム数が対応付けられたデータベースを読み込む
		void loadGroupNameToFramesDatabase(std::string databaseFilePath, bool passFirstLine = true);

		// 画像をメモリに読み込む
		void loadImage(std::string imageName);
		void loadImage(std::string imageName, std::string imageFilePath); // 主に臨時テスト用
		// 集合画像をメモリに読み込む
		void loadGroup(std::string groupName);
		void loadGroup(std::string groupName, std::string imageFilePath, int allNum, int xNum, int yNum, int sizeX, int sizeY);  // 主に臨時テスト用

		// メモリから画像を破棄する
		void deleteImage(std::string imageName);
		// メモリから集合画像を破棄する
		void deleteGroup(std::string groupName);

		// すべての画像をメモリから破棄する
		void deleteAllImage();
		// すべての集合画像をメモリから破棄する
		void deleteAllGroup();
		// すべての画像(集合画像を含む)をメモリから破棄する
		void deleteAllImageAndGroup();

		// 画像のハンドルを取得
		int getImageHandle(std::string imageName) const;
		// 集合画像の指定した画像のハンドルを取得
		int getImageHandleInGroup(std::string groupName, int id) const;
		// 集合写真をアニメーションとして描画するために画像のハンドルを取得
		int getImageHandleInAnime(std::string groupName, AnimeElapsedData* elapsedData) const;
		int getImageHandleInAnime(std::string groupName, AnimeElapsedData* elapsedData, const std::vector<int>& frameVector) const;

	protected:
		ImageManager(); // 外部でのインスタンス作成は禁止
		virtual ~ImageManager();
	};
}

#endif // !image_manager_h