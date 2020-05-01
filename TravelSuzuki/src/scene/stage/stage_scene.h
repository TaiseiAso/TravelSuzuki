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
		const unsigned int whiteColor_ = GetColor(255, 255, 255); // ���F

		// �u���b�N�t�@�N�g��
		std::unique_ptr<object::block::BlockFactory> blockFactory_;

		// �v���C���[
		std::shared_ptr<object::character::player::Player> player_;
		
		// �u���b�N�̔z��
		std::shared_ptr<object::block::Block> blockArray_[1][1];

		// �V�[���̏���������
		virtual void initialize() override;
		// �V�[���̏I������
		virtual void finalize() override;

		// ���͂ɂ��ω�
		virtual void action() override;
		// �X�e�b�v���Ƃɐi�ޏ���
		virtual void update() override;
		// ��Ԃ̕`��
		virtual void draw() const override;

	public:
		// �R���X�g���N�^
		StageScene();
		// �f�X�g���N�^
		virtual ~StageScene();
	};
}

#endif // !stage_scene_h