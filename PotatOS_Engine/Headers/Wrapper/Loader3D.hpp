#pragma once

#include <DLLInclude.hpp>

#include <vector>
#include <map>
#include <string>

#include <DataStructure/Animation/AnimData.hpp>
#include <DataStructure/Animation/Rig.hpp>
#include <Resource/Mesh.hpp>

namespace Wrapper
{
	const DataStructure::Animation::MeshData POTATOS_ENGINE_API ProcessModel(const std::string& p_path);
	const DataStructure::Animation::AnimationData POTATOS_ENGINE_API ProcessAnimation(const std::string& p_animationPath, DataStructure::Animation::Rig* p_rig);
}
