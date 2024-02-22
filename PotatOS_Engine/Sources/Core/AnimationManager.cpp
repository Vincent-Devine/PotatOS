#include "pch.h"
#include <Wrapper/Loader3D.hpp>
#include <Core/AnimationManager.hpp>
#include <DebugSystem/Assertion.hpp>

namespace Core
{
	AnimationManager* AnimationManager::singleton = nullptr;

	AnimationManager* AnimationManager::Get()
	{
		if (singleton == nullptr)
		{
			singleton = new AnimationManager;
		}
		return singleton;
	}

	DataStructure::Animation::Animation* AnimationManager::UseAnimation(const std::string& p_path, DataStructure::Animation::Rig* p_rig)
	{
		if (!p_rig)
			return nullptr;

		DataStructure::Animation::Animation* animation = GetAnimation(p_path);
		if (!animation)
		{
			animation = CreateAnimation(p_path, p_rig);
		}

		return animation;
	}

	DataStructure::Animation::Rig* AnimationManager::UseRig(const std::string& p_path)
	{
		DataStructure::Animation::Rig* rig = GetRig(p_path);
		if (!rig)
		{
			Log::Print("Rig not found!", LOG_LEVEL_TYPE::Warning);
		}

		return rig;
	}

	void AnimationManager::Delete()
	{
		for (std::map<std::string, DataStructure::Animation::Animation*>::iterator it = animations.begin(); it != animations.end(); it++)
		{
			delete it->second;
		}

		for (std::map<std::string, DataStructure::Animation::Rig*>::iterator it = rigs.begin(); it != rigs.end(); it++)
		{
			delete it->second;
		}
	}

	void AnimationManager::AddRig(DataStructure::Animation::Rig* p_rig)
	{
		rigs.insert_or_assign(p_rig->path, p_rig);
	}

	DataStructure::Animation::Animation* AnimationManager::GetAnimation(const std::string& p_path)
	{
		DataStructure::Animation::Animation* animation = nullptr;

		if (animations.count(p_path) != 0)
		{
			animation = animations.find(p_path)->second;
		}

		return animation;
	}

	DataStructure::Animation::Rig* AnimationManager::GetRig(const std::string& p_path)
	{
		DataStructure::Animation::Rig* rig = nullptr;

		if (rigs.count(p_path) != 0)
		{
			rig = rigs.find(p_path)->second;
		}

		return rig;
	}

	DataStructure::Animation::Animation* AnimationManager::CreateAnimation(const std::string& p_path, DataStructure::Animation::Rig* p_rig)
	{
		DataStructure::Animation::AnimationData animationData = Wrapper::ProcessAnimation(p_path, p_rig);
		DataStructure::Animation::Animation* animation = new DataStructure::Animation::Animation(animationData, p_path);
		animations.insert_or_assign(p_path, animation);
		Log::Print("Add animation " + p_path + " in animations", LOG_LEVEL_TYPE::Notification);
		return animation;
	}
}