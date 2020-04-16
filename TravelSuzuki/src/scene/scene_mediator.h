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
			bool isMovingScene; // �V�[�����ړ������ǂ���
			SceneID nextSceneID; // �ړ���̃V�[��ID
			bool isFadeOut; // �t�F�[�h�A�E�g�����ǂ���
			int moveSceneFrame; // �V�[���ړ��ɗv����t���[����
			int fadeLevel; // �t�F�[�h�̂����� (�ő��moveSceneFrame)
			std::vector<SceneID> createSceneIDVector; // �ړ����ɍ쐬����V�[����ID���X�g
			std::vector<SceneID> deleteSceneIDVector; // �ړ����ɔj������V�[����ID���X�g
			bool allowChangeMasterVolumeFadeOut; // �t�F�[�h�A�E�g���Ƀ}�X�^�[���ʂ�ύX���邩�ǂ���
			bool allowChangeMasterVolumeFadeIn; // �t�F�[�h�C�����Ƀ}�X�^�[���ʂ�ύX���邩�ǂ���
			SceneMoveEffectID sceneMoveEffectID; // �V�[���ړ����̉��oID
		} MoveSceneData;

		// �V�[���ړ��Ɋւ���\���̃I�u�W�F�N�g
		MoveSceneData moveSceneData_;

		// �e��V�[�����o�̕`��
		void drawScreenOneColor(unsigned int color) const;

	public:
		// �R���X�g���N�^
		SceneMediator();
		// �f�X�g���N�^
		~SceneMediator();

		// ���݃V�[���ړ������ǂ������擾
		bool isMovingScene() const;

		// �ړ���̃V�[��ID���擾����
		SceneID getNextSceneID() const;
		// �쐬����V�[����ID���X�g���擾����
		const std::vector<SceneID>& getCreateSceneIDVector() const;
		// �j������V�[����ID���X�g���擾����
		const std::vector<SceneID>& getDeleteSceneIDVector() const;
		/*
			�V�[���ړ��󋵂��擾���� (-1.0~1.0�̊Ԃ̒l)
			-1.0~0.0: �t�F�[�h�C����
			0.0: �V�[���ړ����ł͂Ȃ� (�������͑����V�[���ړ��̏u��)
			0.0~1.0: �t�F�[�h�A�E�g��
		*/
		float getFadeRatio() const;

		// �V�[���ړ��Ɋւ���e��p�����[�^��ݒ肷��
		void setMoveSceneFrame(int moveSceneFrame);
		void setAllowChangeMasterVolumeFade(bool allowChangeMasterVolumeFadeOut, bool allowChangeMasterVolumeFadeIn);
		void setSceneMoveEffectID(SceneMoveEffectID sceneMoveEffectID);

		// �V�[���ړ����J�n����
		void moveScene(SceneID nextSceneID);
		void moveScene(SceneID nextSceneID, std::vector<SceneID> createSceneIDVector, std::vector<SceneID> deleteSceneIDVector);
		
		/*
			�V�[���ړ����X�V����
			return: true->�V�[���ړ��^�C�~���O�ł���, false->�V�[���ړ��^�C�~���O�ł͂Ȃ�
		*/
		bool updateMoveScene();
		
		// �V�[���ړ��̉��o��`�悷��
		void drawSceneMoveEffect() const;
	};
}

#endif // !scene_mediator_h