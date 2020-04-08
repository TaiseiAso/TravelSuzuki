#ifndef fps_controller_h
#define fps_controller_h

#include "Dxlib.h"

class FPSController
{
private:
	int startTime_; // 測定開始時刻
	int count_; // カウンタ
	float fps_; // 現在の推定FPS
	static const int N = 30; // FPS推定のために平均を取るサンプル数
	static const int FPS = 60; // 設定したFPS

public:
	// コンストラクタ
	FPSController();
	// デストラクタ
	~FPSController();

	// 更新
	void update();
	// テスト用にFPS描画
	void draw() const;
	// FPS固定のため一定時間待機
	void wait() const;
};

#endif // !fps_controller_h

