#ifndef timer_h
#define timer_h

#include "DxLib.h"

namespace game::timer
{
	class Timer
	{
	private:
		const unsigned int whiteColor_ = GetColor(255, 255, 255); // 白色
		const unsigned int redColor_ = GetColor(255, 60, 60); // 赤色

		int x_; // 左上のX座標
		int y_; // 右上のY座標
		float remainTime_; // 残り時間
		bool isFinished_; // 時間制限フラグ
		bool isStop_; // 一時停止フラグ

		int fontHandle_; // フォントのハンドル

		// コピーコンストラクタを禁止する
		Timer(const Timer&) = delete;
		Timer(Timer&&) = delete;

		// コピー代入演算子を禁止する
		Timer& operator=(const Timer&) = delete;
		Timer& operator=(Timer&&) = delete;

	public:
		// コンストラクタ
		Timer(int x, int y, int fontSize);
		// デストラクタ
		~Timer();

		// ステップごとに進む処理
		void update();
		// 状態の描画
		void draw() const;

		// 残り時間を取得する
		float getRemainTime() const;
		// 時間制限になったかを取得する
		bool isFinished() const;
		// 一時停止しているかを取得する
		bool isStop() const;

		// 残り時間を設定する
		void setRemainTime(float remainTime);
		// 一時停止する
		void stop();
		// 一時停止を解除する
		void resume();

	};
}

#endif // !timer_h