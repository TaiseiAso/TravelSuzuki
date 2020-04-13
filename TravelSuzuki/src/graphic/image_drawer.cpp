#include <fstream>
#include <sstream>
#include <string>
#include "image_drawer.h"
#include "../utils/string_util.h"
#include "DxLib.h"

namespace game::graphic
{
	void ImageDrawer::loadImageNameToPathDatabase(std::string databaseFilePath, bool passFirstLine)
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
	
	void ImageDrawer::loadGroupNameToDivDataDatabase(std::string databaseFilePath, bool passFirstLine)
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

	void ImageDrawer::loadGroupNameToFramesDatabase(std::string databaseFilePath, bool passFirstLine)
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
				for (int i = 1; i < static_cast<int>(strVec.size()); i++) frameVector.push_back(stoi(strVec[i]));
				groupNameToFrameVector_[strVec[0]] = frameVector;
			}
		}
	}

	void ImageDrawer::loadImage(std::string imageName)
	{
		auto itrImage = imageNameToPath_.find(imageName);
		if (itrImage != imageNameToPath_.end())
		{
			loadImage(imageName, itrImage->second);
		}
	}
	
	void ImageDrawer::loadImage(std::string imageName, std::string imageFilePath)
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
	
	void ImageDrawer::loadGroup(std::string groupName)
	{
		auto itrImage = imageNameToPath_.find(groupName);
		if (itrImage != imageNameToPath_.end())
		{
			auto itrGroup = groupNameToDivData_.find(groupName);
			if (itrGroup != groupNameToDivData_.end())
			{
				ImageDivData imageDivData = itrGroup->second;
				loadGroup(
					groupName, itrImage->second,
					imageDivData.allNum, imageDivData.xNum, imageDivData.yNum, imageDivData.sizeX, imageDivData.sizeY
				);
			}
		}
	}
	
	void ImageDrawer::loadGroup(std::string groupName, std::string imageFilePath, int allNum, int xNum, int yNum, int sizeX, int sizeY)
	{
		auto itrGroup = groupNameToHandleVector_.find(groupName);
		if (itrGroup == groupNameToHandleVector_.end())
		{
			int* imageHandleList = new int[allNum];
			if (LoadDivGraph(imageFilePath.c_str(), allNum, xNum, yNum, sizeX, sizeY, imageHandleList) == 0)
			{
				std::vector<int> imageHandleVector;
				for (int i = 0; i < allNum; i++) imageHandleVector.push_back(imageHandleList[i]);
				groupNameToHandleVector_[groupName] = imageHandleVector;
			}
			delete[] imageHandleList;
		}
	}

	void ImageDrawer::deleteImage(std::string imageName)
	{
		auto itrImage = imageNameToHandle_.find(imageName);
		if (itrImage != imageNameToHandle_.end())
		{
			DeleteGraph(itrImage->second);
			imageNameToHandle_.erase(itrImage);
		}
	}
	
	void ImageDrawer::deleteGroup(std::string groupName)
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

	void ImageDrawer::deleteAllImage()
	{
		for (const auto& itrImage : imageNameToHandle_)
		{
			DeleteGraph(itrImage.second);
		}
		imageNameToHandle_.clear();
	}
	
	void ImageDrawer::deleteAllGroup()
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

	void ImageDrawer::deleteAllImageAndGroup()
	{
		deleteAllImage();
		deleteAllGroup();
	}

	int ImageDrawer::getImageHandle(std::string imageName) const
	{
		auto itrImage = imageNameToHandle_.find(imageName);
		if (itrImage != imageNameToHandle_.end())
		{
			return itrImage->second;
		}
		return -1;
	}

	int ImageDrawer::getImageHandleInGroup(std::string groupName, int id) const
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
	
	int ImageDrawer::getImageHandleInAnime(std::string groupName, int& elapsedFrame, int& elapsedSheet) const
	{
		auto itrGroup = groupNameToFrameVector_.find(groupName);
		if (itrGroup != groupNameToFrameVector_.end())
		{
			return getImageHandleInAnime(groupName, elapsedFrame, elapsedSheet, itrGroup->second);
		}
		return -1;
	}

	int ImageDrawer::getImageHandleInAnime(std::string groupName, int& elapsedFrame, int& elapsedSheet, std::vector<int> frameVector) const
	{
		if (elapsedFrame >= 0 && elapsedSheet >= 0)
		{
			auto itrGroup = groupNameToHandleVector_.find(groupName);
			if (itrGroup != groupNameToHandleVector_.end())
			{
				if (static_cast<int>(itrGroup->second.size()) > elapsedSheet)
				{
					int imageHandle = itrGroup->second[elapsedSheet];
					elapsedFrame++;
					int frame = 0;
					if (static_cast<int>(frameVector.size()) > elapsedSheet) frame = frameVector[elapsedSheet];
					else if (!frameVector.empty()) frame = frameVector.back();
					if (frame <= elapsedFrame)
					{
						elapsedFrame = 0;
						elapsedSheet++;
						if (itrGroup->second.size() == elapsedSheet)
						{
							elapsedSheet = 0;
						}
					}
					return imageHandle;
				}
			}
		}
		return -1;
	}

	ImageDrawer::ImageDrawer() {}
	ImageDrawer::~ImageDrawer()
	{
		deleteAllImageAndGroup();
		imageNameToPath_.clear();
		groupNameToDivData_.clear();
		for (auto& itrGroup : groupNameToFrameVector_)
		{
			itrGroup.second.clear();
			itrGroup.second.shrink_to_fit();
		}
		groupNameToFrameVector_.clear();
	}
}