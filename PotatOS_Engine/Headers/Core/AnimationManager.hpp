#pragma once

#include <vector>
#include <DataStructure/Animation/Animation.hpp>
#include <DataStructure/Animation/Rig.hpp>
#include <Resource/Mesh.hpp>

namespace Core
{
	class AnimationManager
	{
		// Attributes
	private:
		static AnimationManager* singleton;
		std::map<std::string, DataStructure::Animation::Animation*> animations;
		std::map<std::string, DataStructure::Animation::Rig*> rigs;
		
		// Methods
	public:
		static AnimationManager* Get();

		DataStructure::Animation::Animation* UseAnimation(const std::string& p_path, DataStructure::Animation::Rig* p_rig);
		DataStructure::Animation::Rig* UseRig(const std::string& p_path);
		
		void Delete();

		void AddRig(DataStructure::Animation::Rig* p_rig);

	private:
		DataStructure::Animation::Animation* GetAnimation(const std::string& p_path);
		DataStructure::Animation::Rig* GetRig(const std::string& p_path);
		
		DataStructure::Animation::Animation* CreateAnimation(const std::string& p_path, DataStructure::Animation::Rig* p_rig);
	};
}
