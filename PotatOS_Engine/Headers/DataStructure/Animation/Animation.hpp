#pragma once

#include <DLLInclude.hpp>
#include <vector>
#include <map>

#include <Math/Mat4.inl>
#include <Resource/Mesh.hpp>
#include <DataStructure/Animation/Bone.hpp>
#include <DataStructure/Animation/AnimData.hpp>

#include <Refureku/Refureku.h>
#include <Refureku/Generated/Animation.rfkh.h>

namespace DataStructure::Animation RFKNamespace()
{
	class RFKClass() POTATOS_ENGINE_API Animation
	{
		// Attributes
	private:
		RFKField()
		std::string path;

		RFKField()
		float duration;

		int tickPerSecond;
		std::vector<Bone> bones;
		NodeData nodeData;
		std::map<std::string, BoneInfo> boneInfos;
		float currentTime;

		// Methods
	public:
		Animation();
		Animation(const AnimationData& p_animationData, const std::string& p_path);
	
		Bone* FindBone(const std::string& p_name);
		bool UpdateTime(const float p_deltaTime);

		const std::string& GetPath() const { return path; };
		const float GetDuration() const { return duration; };
		const int GetTicksPerSecond() const { return tickPerSecond; };
		const std::map<std::string, BoneInfo>& GetBoneInfos() const { return boneInfos; };
		const NodeData& GetRootNode() { return nodeData; };
		const float GetCurrentTimeAnimation() { return currentTime; };

		void SetCurrentTime(const float p_currentTime) { currentTime = p_currentTime; };

		DataStructure_Animation_Animation_GENERATED
	};
}
File_Animation_GENERATED
