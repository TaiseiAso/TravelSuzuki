#ifndef title_scene_h
#define title_scene_h

#include "base_scene.h"
#include "DxLib.h"

namespace game::scene::title
{
	class TitleScene : public BaseScene
	{
	private:
		// タイトル画面専用 //////////////////////////////////////
		// << 列挙型 >>
		enum class Mode
		{
			FIRST,
			MENU
		};

		// << 定数 >>
		const unsigned int whiteColor_ = GetColor(255, 255, 255); // 白色
		const unsigned int blackColor_ = GetColor(0, 0, 0); // 黒色
		const unsigned int blueColor_ = GetColor(80, 60, 240); // 青色
		const unsigned int greenColor_ = GetColor(60, 200, 80);  // 緑色
		const unsigned int redColor_ = GetColor(200, 60, 80);  // 赤色

		// << 変数 >>
		int elapsedFrame_; // 経過フレーム数
		Mode mode_; // 画面状況
		int cursor_; // カーソル位置

		// << 操作関連 >>
		void actionPleasePressSpaceKey(); // ゲーム開始直後の操作
		void actionMenu(); // メニュー画面の操作

		// << 描画関連 >>
		void drawBackGround() const; // 背景描画
		void drawTitleLogo() const; // タイトルロゴ描画
		void drawPleasePressSpaceKey() const; // 「スペースキーを押してください」メッセージ描画
		void drawMenu() const; // メニュー描画
		//////////////////////////////////////////////////////////

		// シーンの初期化処理
		void initialize() override;
		// シーンの終了処理
		void finalize() override;

		// 入力による変化
		void action() override;
		// ステップごとに進む処理
		void update() override;
		// 状態の描画
		void draw() const override;

	public:
		// コンストラクタ
		TitleScene();
		// デストラクタ
		~TitleScene();
	};
}

#endif // !title_scene_h