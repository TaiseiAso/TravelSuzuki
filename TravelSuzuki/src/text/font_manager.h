#ifndef font_manager_h
#define font_manager_h

#include <unordered_map>
#include "../singleton/singleton.h"

namespace game::text
{
	class FontManager : public Singleton<FontManager>
	{
		friend class Singleton<FontManager>; // Singleton でのインスタンス作成は許可

	private:

	public:

	protected:
		FontManager(); // 外部でのインスタンス作成は禁止
		~FontManager();
	};
}

#endif // !font_manager_h