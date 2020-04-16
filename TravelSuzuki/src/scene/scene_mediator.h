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
			int moveSceneFrame; // シーン移動に要するフレーム数
			int fadeLevel; // フェードのかかり具合 (最大はmoveSceneFrame)
			std::vector<SceneID> createSceneIDVector; // 移動時に作成するシーンのIDリスト
			std::vector<SceneID> deleteSceneIDVector; // 移動時に破棄するシーンのIDリスト
			bool allowChangeMasterVolumeFadeOut; // フェードアウト時にマスター音量を変更するかどうか
			bool allowChangeMasterVolumeFadeIn; // フェードイン時にマスター音量を変更するかどうか
			SceneMoveEffectID sceneMoveEffectID; // シーン移動時の演出ID
		} MoveSceneData;

		// シーン移動に関する構造体オブジェクト
		MoveSceneData moveSceneData_;

		// 各種シーン演出の描画
		void drawScreenOneColor(unsigned int color) const;

	public:
		// コンストラクタ
		SceneMediator();
		// デストラクタ
		~SceneMediator();

		// 現在シーン移動中かどうかを取得
		bool isMovingScene() const;

		// 移動先のシーンIDを取得する
		SceneID getNextSceneID() const;
		// 作成するシーンのIDリストを取得する
		const std::vector<SceneID>& getCreateSceneIDVector() const;
		// 破棄するシーンのIDリストを取得する
		const std::vector<SceneID>& getDeleteSceneIDVector() const;
		/*
			シーン移動状況を取得する (-1.0~1.0の間の値)
			-1.0~0.0: フェードイン中
			0.0: シーン移動中ではない (もしくは即時シーン移動の瞬間)
			0.0~1.0: フェードアウト中
		*/
		float getFadeRatio() const;

		// シーン移動に関する各種パラメータを設定する
		void setMoveSceneFrame(int moveSceneFrame);
		void setAllowChangeMasterVolumeFade(bool allowChangeMasterVolumeFadeOut, bool allowChangeMasterVolumeFadeIn);
		void setSceneMoveEffectID(SceneMoveEffectID sceneMoveEffectID);

		// シーン移動を開始する
		void moveScene(SceneID nextSceneID);
		void moveScene(SceneID nextSceneID, const std::vector<SceneID>& createSceneIDVector, const std::vector<SceneID>& deleteSceneIDVector);
		
		/*
			シーン移動を更新する
			return: true->シーン移動タイミングである, false->シーン移動タイミングではない
		*/
		bool updateMoveScene();
		
		// シーン移動の演出を描画する
		void drawSceneMoveEffect() const;
	};
}

#endif // !scene_mediator_h