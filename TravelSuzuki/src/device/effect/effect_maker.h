#ifndef effect_maker_h
#define effect_maker_h

#include "singleton/singleton.h"

namespace game::effect
{
	class EffectMaker : public Singleton<EffectMaker>
	{
		friend class Singleton<EffectMaker>; // Singleton でのインスタンス作成は許可

	public:
		void test();

	protected:
		EffectMaker() {} // 外部でのインスタンス作成は禁止
		virtual ~EffectMaker() {}
	};
}

#endif // !effect_maker_h

