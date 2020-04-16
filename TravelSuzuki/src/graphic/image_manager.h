#ifndef image_manager_h
#define image_manager_h

#include <unordered_map>
#include "../singleton/singleton.h"

namespace game::graphic
{
	typedef struct {
		int frame; // ����摜�ɂ�����o�߃t���[����
		int sheet; // �A�j���̕\���摜�ԍ�
	} AnimeElapsedData;

	class ImageManager : public Singleton<ImageManager>
	{
		friend class Singleton<ImageManager>; // Singleton �ł̃C���X�^���X�쐬�͋���

	private:
		typedef struct {
			int allNum; // �摜�̕�������
			int xNum; // �摜�̉��ɑ΂��镪����
			int yNum; // �摜�̏c�ɑ΂��镪����
			int sizeX; // ������̉摜�̉��̃T�C�Y
			int sizeY; // ������̉摜�̏c�̃T�C�Y
		} ImageDivData;

		// �������ɓǂݍ��މ摜�̖��O�ƃt�@�C���p�X�̃}�b�v
		std::unordered_map<std::string, std::string> imageNameToPath_;
		// �������ɓǂݍ��ޏW���摜�̖��O�Ɖ摜�̕������@�̍\���̂̃}�b�v
		std::unordered_map<std::string, ImageDivData> groupNameToDivData_;
		// �������ɓǂݍ��ޏW���摜�̖��O�ƕ�����̉摜�̕`��t���[�����̃��X�g�̃}�b�v
		std::unordered_map<std::string, std::vector<int>> groupNameToFrameVector_;
		
		// �������ɓǂݍ��񂾉摜�̖��O�ƃn���h���̃}�b�v
		std::unordered_map<std::string, int> imageNameToHandle_;
		// �������ɓǂݍ��񂾏W���摜�̖��O�ƃn���h���̃��X�g�̃}�b�v
		std::unordered_map<std::string, std::vector<int>> groupNameToHandleVector_;

	public:
		// �摜(�W���摜���܂�)�̖��O�ƃt�@�C���p�X���Ή��t����ꂽ�f�[�^�x�[�X��ǂݍ���
		void loadImageNameToPathDatabase(std::string databaseFilePath, bool passFirstLine = true);
		// �W���摜�̖��O�Ɖ摜�̕������@���Ή��t����ꂽ�f�[�^�x�[�X��ǂݍ���
		void loadGroupNameToDivDataDatabase(std::string databaseFilePath, bool passFirstLine = true);
		// �W���摜�̖��O�ƕ�����̉摜�̕`��t���[�������Ή��t����ꂽ�f�[�^�x�[�X��ǂݍ���
		void loadGroupNameToFramesDatabase(std::string databaseFilePath, bool passFirstLine = true);

		// �摜���������ɓǂݍ���
		void loadImage(std::string imageName);
		void loadImage(std::string imageName, std::string imageFilePath); // ��ɗՎ��e�X�g�p
		// �W���摜���������ɓǂݍ���
		void loadGroup(std::string groupName);
		void loadGroup(std::string groupName, std::string imageFilePath, int allNum, int xNum, int yNum, int sizeX, int sizeY);  // ��ɗՎ��e�X�g�p

		// ����������摜��j������
		void deleteImage(std::string imageName);
		// ����������W���摜��j������
		void deleteGroup(std::string groupName);

		// ���ׂẲ摜������������j������
		void deleteAllImage();
		// ���ׂĂ̏W���摜������������j������
		void deleteAllGroup();
		// ���ׂẲ摜(�W���摜���܂�)������������j������
		void deleteAllImageAndGroup();

		// �摜�̃n���h�����擾
		int getImageHandle(std::string imageName) const;
		// �W���摜�̎w�肵���摜�̃n���h�����擾
		int getImageHandleInGroup(std::string groupName, int id) const;
		// �W���ʐ^���A�j���[�V�����Ƃ��ĕ`�悷�邽�߂ɉ摜�̃n���h�����擾
		int getImageHandleInAnime(std::string groupName, AnimeElapsedData* elapsedData) const;
		int getImageHandleInAnime(std::string groupName, AnimeElapsedData* elapsedData, std::vector<int> frameVector) const;

	protected:
		ImageManager(); // �O���ł̃C���X�^���X�쐬�͋֎~
		virtual ~ImageManager();
	};
}

#endif // !image_manager_h