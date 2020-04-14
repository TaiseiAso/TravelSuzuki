#ifndef scene_mediator_h
#define scene_mediator_h

#include <vector>
#include "scene_enum.h"

namespace game::scene
{
	class SceneMediator
	{
	private:
		typedef struct {
			bool isMovingScene; // シーンを移動中かどうか
			SceneID nextSceneID; // 移動先のシーンID
			bool isFadeOut; // フェードアウト中かどうか
			int moveFrame; // シーン移動に要するフレーム数
			int fadeLevel; // フェードのかかり具合 (最大はmoveFrame)
			std::vector<SceneID> createSceneIDVector; // 移動時に作成するシーンのIDリスト
			std::vector<SceneID> deleteSceneIDVector; // 移動時に破棄するシーンのIDリスト
		} MoveSceneData;

		// シーン移動に関する構造体オブジェクト
		MoveSceneData moveSceneData_;

	public:
		// コンストラクタ
		SceneMediator();
		// デストラクタ
		~SceneMediator();

		// 現在シーン移動中かどうかを取得
		bool isMovingScene() const;

		// 移動先のシーンIDを取得する (シーン移動中でなければSceneID::NONEを返す)
		SceneID getNextSceneID();
		// 作成するシーンのIDリストを取得する (シーン移動中でなければ空を返す)
		std::vector<SceneID> getCreateSceneIDVector();
		// 破棄するシーンのIDリストを取得する (シーン移動中でなければ空を返す)
		std::vector<SceneID> getDeleteSceneIDVector();

		// シーン移動を開始する
		void moveScene(SceneID nextSceneID, int moveFrame);
		void moveScene(SceneID nextSceneID, int moveFrame, std::vector<SceneID> createSceneIDVector, std::vector<SceneID> deleteSceneIDVector);

		// シーン移動を更新する
		bool update();
		
		// シーン移動の演出を描画する
		void draw() const;
	};
}

#endif // !scene_mediator_h