#include <fstream>
#include <sstream>
#include <string>
#include "image_manager.h"
#include "../utils/string_util.h"
#include "DxLib.h"

namespace game::graphic
{
	void ImageManager::loadImageNameToPathDatabase(std::string databaseFilePath, bool passFirstLine)
	{
		imageNameToPath_.clear();

		std::ifstream ifs(databaseFilePath);
		std::string line;
		if (passFirstLine) std::getline(ifs, line); // àÍçsñ⁄ÇÕîÚÇŒÇ∑
		while (std::getline(ifs, line))
		{
			std::vector<std::string> strVec = StringUtil::split(line, ',');
			if (strVec.size() >= 2) imageNameToPath_[strVec[0]] = strVec[1];
		}
	}
	
	void ImageManager::loadGroupNameToDivDataDatabase(std::string databaseFilePath, bool passFirstLine)
	{
		groupNameToDivData_.clear();

		std::ifstream ifs(databaseFilePath);
		std::string line;
		if (passFirstLine) std::getline(ifs, line); // àÍçsñ⁄ÇÕîÚÇŒÇ∑
		while (std::getline(ifs, line))
		{
			std::vector<std::string> strVec = StringUtil::split(line, ',');
			if (strVec.size() >= 6)
			{
				groupNameToDivData_[strVec[0]] =
				{
					stoi(strVec[1]), stoi(strVec[2]), stoi(strVec[3]), stoi(strVec[4]), stoi(strVec[5])
				};
			}
		}
	}

	void ImageManager::loadGroupNameToFramesDatabase(std::string databaseFilePath, bool passFirstLine)
	{
		for (auto& itrGroup : groupNameToFrameVector_)
		{
			itrGroup.second.clear();
			itrGroup.second.shrink_to_fit();
		}
		groupNameToFrameVector_.clear();
		
		std::ifstream ifs(databaseFilePath);
		std::string line;
		if (passFirstLine) std::getline(ifs, line); // àÍçsñ⁄ÇÕîÚÇŒÇ∑
		while (std::getline(ifs, line))
		{
			std::vector<std::string> strVec = StringUtil::split(line, ',');
			if (strVec.size() >= 2)
			{
				std::vector<int> frameVector;
				for (int i = 1; i < static_cast<int>(strVec.size()); ++i) frameVector.push_back(stoi(strVec[i]));
				groupNameToFrameVector_[strVec[0]] = std::move(frameVector);
			}
		}
	}

	void ImageManager::loadImage(std::string imageName)
	{
		auto itrImage = imageNameToPath_.find(imageName);
		if (itrImage != imageNameToPath_.end())
		{
			loadImage(imageName, itrImage->second);
		}
	}
	
	void ImageManager::loadImage(std::string imageName, std::string imageFilePath)
	{
		auto itrImage = imageNameToHandle_.find(imageName);
		if (itrImage == imageNameToHandle_.end())
		{
			int imageHandle = LoadGraph(imageFilePath.c_str());
			if (imageHandle != -1)
			{
				imageNameToHandle_[imageName] = imageHandle;
			}
		}
	}
	
	void ImageManager::loadGroup(std::string groupName)
	{
		auto itrImage = imageNameToPath_.find(groupName);
		if (itrImage != imageNameToPath_.end())
		{
			auto itrGroup = groupNameToDivData_.find(groupName);
			if (itrGroup != groupNameToDivData_.end())
			{
				const ImageDivData& imageDivData = itrGroup->second;
				loadGroup(
					groupName, itrImage->second,
					imageDivData.allNum, imageDivData.xNum, imageDivData.yNum, imageDivData.sizeX, imageDivData.sizeY
				);
			}
		}
	}
	
	void ImageManager::loadGroup(std::string groupName, std::string imageFilePath, int allNum, int xNum, int yNum, int sizeX, int sizeY)
	{
		auto itrGroup = groupNameToHandleVector_.find(groupName);
		if (itrGroup == groupNameToHandleVector_.end())
		{
			int* imageHandleList = new int[allNum];
			if (LoadDivGraph(imageFilePath.c_str(), allNum, xNum, yNum, sizeX, sizeY, imageHandleList) == 0)
			{
				std::vector<int> imageHandleVector;
				for (int i = 0; i < allNum; ++i) imageHandleVector.push_back(imageHandleList[i]);
				groupNameToHandleVector_[groupName] = std::move(imageHandleVector);
			}
			delete[] imageHandleList;
		}
	}

	void ImageManager::deleteImage(std::string imageName)
	{
		auto itrImage = imageNameToHandle_.find(imageName);
		if (itrImage != imageNameToHandle_.end())
		{
			DeleteGraph(itrImage->second);
			imageNameToHandle_.erase(itrImage);
		}
	}
	
	void ImageManager::deleteGroup(std::string groupName)
	{
		auto itrGroup = groupNameToHandleVector_.find(groupName);
		if (itrGroup != groupNameToHandleVector_.end())
		{
			for (const int& imageHandle : itrGroup->second)
			{
				DeleteGraph(imageHandle);
			}
			itrGroup->second.clear();
			itrGroup->second.shrink_to_fit();
			groupNameToHandleVector_.erase(itrGroup);
		}
	}

	void ImageManager::deleteAllImage()
	{
		for (const auto& itrImage : imageNameToHandle_)
		{
			DeleteGraph(itrImage.second);
		}
		imageNameToHandle_.clear();
	}
	
	void ImageManager::deleteAllGroup()
	{
		for (auto& itrGroup : groupNameToHandleVector_)
		{
			for (const int& imageHandle : itrGroup.second)
			{
				DeleteGraph(imageHandle);
			}
			itrGroup.second.clear();
			itrGroup.second.shrink_to_fit();
		}
		groupNameToHandleVector_.clear();
	}

	void ImageManager::deleteAllImageAndGroup()
	{
		deleteAllImage();
		deleteAllGroup();
	}

	int ImageManager::getImageHandle(std::string imageName) const
	{
		auto itrImage = imageNameToHandle_.find(imageName);
		if (itrImage != imageNameToHandle_.end())
		{
			return itrImage->second;
		}
		return -1;
	}

	int ImageManager::getImageHandleInGroup(std::string groupName, int id) const
	{
		if (id >= 0)
		{
			auto itrGroup = groupNameToHandleVector_.find(groupName);
			if (itrGroup != groupNameToHandleVector_.end())
			{
				if (static_cast<int>(itrGroup->second.size()) > id)
				{
					return itrGroup->second[id];
				}
			}
		}
		return -1;
	}
	
	int ImageManager::getImageHandleInAnime(std::string groupName, AnimeElapsedData* elapsedData) const
	{
		auto itrGroup = groupNameToFrameVector_.find(groupName);
		if (itrGroup != groupNameToFrameVector_.end())
		{
			return getImageHandleInAnime(groupName, elapsedData, itrGroup->second);
		}
		return -1;
	}

	int ImageManager::getImageHandleInAnime(std::string groupName, AnimeElapsedData* elapsedData, const std::vector<int>& frameVector) const
	{
		if (elapsedData && elapsedData->frame >= 0 && elapsedData->sheet >= 0)
		{
			auto itrGroup = groupNameToHandleVector_.find(groupName);
			if (itrGroup != groupNameToHandleVector_.end())
			{
				if (static_cast<int>(itrGroup->second.size()) > elapsedData->sheet)
				{
					int imageHandle = itrGroup->second[elapsedData->sheet];
					int frame = 0;
					if (static_cast<int>(frameVector.size()) > elapsedData->sheet) frame = frameVector[elapsedData->sheet];
					else if (!frameVector.empty()) frame = frameVector.back();
					if (frame <= ++elapsedData->frame)
					{
						elapsedData->frame = 0;
						if (itrGroup->second.size() == ++elapsedData->sheet)
						{
							elapsedData->sheet = 0;
						}
					}
					return imageHandle;
				}
			}
		}
		return -1;
	}

	ImageManager::ImageManager() {}
	ImageManager::~ImageManager()
	{
		deleteAllImageAndGroup();
	}
}