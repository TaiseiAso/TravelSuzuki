#ifndef scene_manager_h
#define scene_manager_h

#include <unordered_map>
#include "singleton/singleton.h"
#include "scene/base_scene.h"

namespace game::scene
{
	class SceneManager : public Singleton<SceneManager>
	{
		friend class Singleton<SceneManager>; // Singleton でのインスタンス作成は許可

	private:
		bool isMovingScene_; // シーンを移動中かどうか
		std::string nextSceneName_; // 移動先のシーン名
		bool isFadeOut_; // フェードアウトかフェードインインかの判別
		int moveSceneFrame_; // シーン移動に要するフレーム数
		int fadeLevel_; // フェードのかかり具合 (最大はmoveSceneFrame)
		bool drawMoveSceneFadeOut_; // フェードアウトを描画するかどうか
		bool drawMoveSceneFadeIn_; // フェードインを描画するかどうか
		unsigned int moveSceneFadeColor_; // シーン移動時のフェード色
		std::vector<std::string> deleteSceneNameVector_; // シーン移動時に破棄するシーン名のリスト

		// シーン名と作成したシーンのマップ
		std::unordered_map<std::string, std::unique_ptr<BaseScene>> nameToScene_;
		// 現在のシーン名
		std::string currentSceneName_;

		// シーンを初期化する
		void initScene(const std::string& sceneName);
		// シーンを終了する
		void finalScene(const std::string& sceneName);

		// 現在のシーンを交換する
		void swapScene();
		// シーン移動を更新する
		void updateMoveScene();

		// シーン移動のフェードイン/アウトを描画する
		void drawMoveSceneFade() const;

		SceneManager(); // 外部でのインスタンス作成は禁止
		~SceneManager();

	public:
		// ステップごとの処理 (終了時falseを返す)
		// 一箇所のみからの呼び出しを許可する
		bool step();

		// 現在シーン移動中かどうかを取得
		bool isMovingScene() const;
		/*
			シーン移動状況を取得する (-1.0~1.0の間の値)
			-1.0~0.0: フェードイン中
			0.0: シーン移動中ではない (もしくは即時シーン移動の瞬間)
			0.0~1.0: フェードアウト中
		*/
		float getFadeRatio() const;

		// シーン移動に要するフレーム数を設定する
		void setMoveSceneFrame(int moveSceneFrame);
		// フェードアウト/インを描画するかどうかを設定する
		void setDrawMoveSceneFade(bool drawMoveSceneFadeOut, bool drawMoveSceneFadeIn);
		// シーン移動時のフェード色を設定する
		void setMoveSceneFadeColor(unsigned int moveSceneFadeColor);

		// シーン移動を開始する
		void moveScene(const std::string& nextSceneName, const std::vector<std::string>& deleteSceneNameVector = {});

		// シーンを作成する
		template <class U>
		void createFirstScene(const std::string& sceneName)
		{
			auto itr = nameToScene_.find(sceneName);
			if (itr == nameToScene_.end())
			{
				nameToScene_[sceneName] = std::make_unique<U>();
				nameToScene_[sceneName]->initialize();
				currentSceneName_ = sceneName;
			}
		}
		template <class U>
		void createScene(const std::string& sceneName)
		{
			auto itr = nameToScene_.find(sceneName);
			if (itr == nameToScene_.end())
			{
				nameToScene_[sceneName] = std::make_unique<U>();
			}

		}
		// シーンを破棄する
		void deleteScene(const std::string& sceneName);
	};
}

#endif // !scene_manager_h