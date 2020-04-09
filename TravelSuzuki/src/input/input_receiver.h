#ifndef input_receiver_h
#define input_receiver_h

#include "../singleton/singleton.h"

namespace game::input
{
	class InputReceiver : public Singleton<InputReceiver>
	{
		friend class Singleton<InputReceiver>; // Singleton でのインスタンス作成は許可

	private:
		int pushKeyFrameArray_[256] = {}; // 全てのキーが押されているフレーム数

	public:
		// キー入力状態を更新する
		void update();
		// 指定したキーが押されているフレーム数を取得する
		int getPushKeyFrame(int keyID) const;

	protected:
		InputReceiver();// 外部でのインスタンス作成は禁止
		virtual ~InputReceiver();
	};
}

#endif // !input_receiver_h