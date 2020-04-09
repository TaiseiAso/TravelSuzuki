#ifndef effect_maker_h
#define effect_maker_h

#include "../singleton/singleton.h"

namespace game::effect
{
	class EffectMaker : public Singleton<EffectMaker>
	{
		friend class Singleton<EffectMaker>; // Singleton �ł̃C���X�^���X�쐬�͋���

	public:
		void test();

	protected:
		EffectMaker() {} // �O���ł̃C���X�^���X�쐬�͋֎~
		virtual ~EffectMaker() {}
	};
}

#endif // !effect_maker_h
