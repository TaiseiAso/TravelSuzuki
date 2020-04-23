#ifndef fps_controller_h
#define fps_controller_h

#include "singleton/singleton.h"
#include "DxLib.h"

namespace game::fps
{
	class FPSController : public Singleton<FPSController>
	{
		friend class Singleton<FPSController>; // Singleton でのインスタンス作成は許可

	private:
		int startTime_; // 測定開始時刻
		int count_; // カウンタ
		float fps_; // 現在の推定FPS

		static const int N = 30; // FPS推定のために平均を取るサンプル数
		static const int FPS = 60; // 設定したFPS

		const unsigned int grayColor_ = GetColor(120, 120, 120); // 灰色

		FPSController(); // 外部でのインスタンス作成は禁止
		~FPSController();

	public:
		// 更新
		void update();
		// テスト用にFPS描画
		void draw() const;
		// FPS固定のため一定時間待機
		void wait() const;
	};
}

#endif // !fps_controller_h

