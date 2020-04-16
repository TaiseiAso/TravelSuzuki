#ifndef scene_enum_h
#define scene_enum_h

namespace game::scene
{
	enum class SceneID
	{
		TEST = -1,
		TITLE,
		GAME,
		RESULT,
		ACHIEVEMENT
	};

	enum class SceneMoveEffectID
	{
		BLACK,
		WHITE
	};
}

#endif // !scene_enum_h