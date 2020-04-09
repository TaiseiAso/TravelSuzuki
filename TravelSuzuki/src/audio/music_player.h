#ifndef music_player_h
#define music_player_h

#include "../singleton/singleton.h"

namespace game::audio
{
	class MusicPlayer : public Singleton<MusicPlayer>
	{
	public:
		void test();

	protected:
		MusicPlayer() {} // 外部でのインスタンス作成は禁止
		virtual ~MusicPlayer() {}
	};
}

#endif // !music_player_h