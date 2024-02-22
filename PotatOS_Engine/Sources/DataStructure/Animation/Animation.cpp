#include "pch.h"
#include <DataStructure/Animation/Animation.hpp>

namespace DataStructure::Animation
{
	Animation::Animation()
	{
	}

	Animation::Animation(const AnimationData& p_animationData, const std::string& p_path)
		: path(p_path)
		, duration(p_animationData.duration)
		, tickPerSecond(p_animationData.ticksPerSecond)
		, bones(p_animationData.bones)
		, nodeData(p_animationData.rootNode)
		, boneInfos(p_animationData.boneInfoMap)
	{
	}

	Bone* Animation::FindBone(const std::string& p_name)
	{
		auto iter = std::find_if(bones.begin(), bones.end(),
			[&](const Bone& Bone)
			{
				return Bone.GetName() == p_name;
			}
		);
		if (iter == bones.end()) return nullptr;
		else return &(*iter);
	}

	bool Animation::UpdateTime(const float p_deltaTime)
	{
		float checkTime = currentTime;
		currentTime += tickPerSecond * p_deltaTime;
		currentTime = static_cast<float>(fmod(currentTime, duration));
		if (checkTime > static_cast<float>(fmod(currentTime + tickPerSecond * p_deltaTime, duration)))
		{
			return true;
		}
		return false;
	}
}
