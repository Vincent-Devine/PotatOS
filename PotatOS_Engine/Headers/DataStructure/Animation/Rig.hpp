#pragma once
#include <map>
#include <string>
#include <DataStructure/Animation/AnimData.hpp>

namespace DataStructure::Animation
{
	struct Rig
	{
		std::string path = "";
		std::map<std::string, DataStructure::Animation::BoneInfo> boneInfos;
		int boneCounter = 0;
	};
}
