#ifndef game_manager_h
#define game_manager_h

#include "pattern/singleton.h"
#include "system/timer/timer.h"
#include "DxLib.h"

namespace game
{
	class GameManager : public Singleton<GameManager>
	{
		friend class Singleton<GameManager>; // Singleton でのインスタンス作成は許可

	private:
		const unsigned int blackColor_ = GetColor(0, 0, 0); // 黒色

		// 時間制限を管理するタイマー
		std::unique_ptr<timer::Timer> timer_;

		GameManager(); // 外部でのインスタンス作成は禁止
		~GameManager();

	public:
		// 入力による変化
		void action();
		// ステップごとに進む処理
		void update();
		// 状態の描画
		void draw() const;

		// タイマーへの参照を返す
		timer::Timer& getTimerRef();
	};
}

#endif // !game_manager_h