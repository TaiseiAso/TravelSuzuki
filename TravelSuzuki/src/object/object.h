#ifndef object_h
#define object_h

namespace game::object
{
	class Object
	{
	public:
		// 初期化処理
		virtual void initialize() {};
		// 終了処理
		virtual void finalize() {};

		// 入力による変化
		virtual void action() {};
		// ステップごとに進む処理
		virtual void update() {};
		// 状態の描画
		virtual void draw() const {};
	};
}

#endif // !object_h