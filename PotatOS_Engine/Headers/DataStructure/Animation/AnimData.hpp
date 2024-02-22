#pragma once

#include <vector>
#include <map>
#include <string>

#include <Common.hpp>
#include <Math/Mat4.inl>

namespace DataStructure
{
	namespace Animation
	{
		class Bone;
	}
}

namespace Resource
{
	class Mesh;
	class Texture;
}

namespace DataStructure::Animation
{
	struct BoneInfo
	{
		int id = -1;
		Math::Mat4 offset = Math::Mat4(0.f);
	};

	struct NodeData
	{
		Math::Mat4 transformation = Math::Mat4::Identity();
		std::string name = "";
		int childrenCount = 0;
		std::vector<NodeData> children;
	};

	struct AnimationData
	{
		float duration = 0;
		int ticksPerSecond = 0;
		std::vector<Bone> bones;
		NodeData rootNode;
		std::map<std::string, BoneInfo> boneInfoMap;
	};

	struct MeshData
	{
		std::string directory = "";
		std::vector<Resource::Mesh> meshes;
		std::vector<Resource::Texture> textures_loaded;
		std::map<std::string, BoneInfo> boneInfoMap;
		int boneCounter = 0;
		bool gammaCorrection = false;
		std::vector<Vertex> vertexBuffer;
		std::vector<unsigned int> indexBuffer;
	};
}
