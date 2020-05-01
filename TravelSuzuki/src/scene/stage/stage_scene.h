#ifndef stage_scene_h
#define stage_scene_h

#include "../base_scene.h"
#include "object/character/player/player.h"
#include "object/block/block_factory.h"
#include "DxLib.h"

namespace game::scene::stage
{
	class StageScene : public BaseScene
	{
	protected:
		const unsigned int whiteColor_ = GetColor(255, 255, 255); // 白色

		// ブロックファクトリ
		std::unique_ptr<object::block::BlockFactory> blockFactory_;

		// プレイヤー
		std::shared_ptr<object::character::player::Player> player_;
		
		// ブロックの配列
		std::shared_ptr<object::block::Block> blockArray_[1][1];

		// シーンの初期化処理
		virtual void initialize() override;
		// シーンの終了処理
		virtual void finalize() override;

		// 入力による変化
		virtual void action() override;
		// ステップごとに進む処理
		virtual void update() override;
		// 状態の描画
		virtual void draw() const override;

	public:
		// コンストラクタ
		StageScene();
		// デストラクタ
		virtual ~StageScene();
	};
}

#endif // !stage_scene_h