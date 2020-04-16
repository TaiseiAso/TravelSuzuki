#ifndef title_scene_h
#define title_scene_h

#include "base_scene.h"
#include "DxLib.h"

namespace game::scene
{
	class TitleScene : public BaseScene
	{
	private:
		// タイトル画面専用 //////////////////////////////////////
		// 各色
		const unsigned int whiteColor = GetColor(255, 255, 255);
		const unsigned int blueColor = GetColor(80, 60, 240);
		const unsigned int greenColor = GetColor(60, 200, 80);

		// 背景描画
		void drawBackGround() const;
		// タイトルロゴ描画
		void drawTitleLogo() const;
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
		TitleScene(std::shared_ptr<SceneMediator>& sceneMediator);
		// デストラクタ
		~TitleScene();
	};
}

#endif // !title_scene_h