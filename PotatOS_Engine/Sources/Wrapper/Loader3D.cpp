#include "pch.h"
#undef min
#undef max

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <Wrapper/Loader3D.hpp>
#include <Math/Quaternion.inl>
#include <DataStructure/Animation/Bone.hpp>
#include <Common.hpp>
#include <Core/AnimationManager.hpp>
#include <DebugSystem/Assertion.hpp>

namespace Wrapper
{
#pragma region UTILITY

	Math::Vector2 GetMyVector2(const aiVector2D& p_vector2)
	{
		return Math::Vector2(p_vector2.x, p_vector2.y);
	}

	Math::Vector3 GetMyVector3(const aiVector3D& p_vector3)
	{
		return Math::Vector3(p_vector3.x, p_vector3.y, p_vector3.z);
	}

	Math::Quaternion GetMyQuaterion(const aiQuaternion& p_quaterion)
	{
		return Math::Quaternion(p_quaterion.x, p_quaterion.y, p_quaterion.z, p_quaterion.w);
	}

	Math::Mat4 GetMyMat4(const aiMatrix4x4& p_mat4)
	{
		Math::Mat4 result;
		result.data[0][0] = p_mat4.a1; result.data[0][1] = p_mat4.a2; result.data[0][2] = p_mat4.a3; result.data[0][3] = p_mat4.a4;
		result.data[1][0] = p_mat4.b1; result.data[1][1] = p_mat4.b2; result.data[1][2] = p_mat4.b3; result.data[1][3] = p_mat4.b4;
		result.data[2][0] = p_mat4.c1; result.data[2][1] = p_mat4.c2; result.data[2][2] = p_mat4.c3; result.data[2][3] = p_mat4.c4;
		result.data[3][0] = p_mat4.d1; result.data[3][1] = p_mat4.d2; result.data[3][2] = p_mat4.d3; result.data[3][3] = p_mat4.d4;
		return result;
	}

	const DataStructure::Animation::BoneData GetBoneData(aiNodeAnim* p_channel)
	{
		DataStructure::Animation::BoneData boneData;

		boneData.numPositions = p_channel->mNumPositionKeys;
		for (int positionIndex = 0; positionIndex < boneData.numPositions; ++positionIndex)
		{
			aiVector3D aiPosition = p_channel->mPositionKeys[positionIndex].mValue;
			float timeStamp = static_cast<float>(p_channel->mPositionKeys[positionIndex].mTime);
			DataStructure::Animation::KeyPosition data;
			data.position = GetMyVector3(aiPosition);
			data.timeStamp = timeStamp;
			boneData.positions.push_back(data);
		}

		boneData.numRotations = p_channel->mNumRotationKeys;
		for (int rotationIndex = 0; rotationIndex < boneData.numRotations; ++rotationIndex)
		{
			aiQuaternion aiOrientation = p_channel->mRotationKeys[rotationIndex].mValue;
			float timeStamp = static_cast<float>(p_channel->mRotationKeys[rotationIndex].mTime);
			DataStructure::Animation::KeyRotation data;
			data.orientation = GetMyQuaterion(aiOrientation);
			data.timeStamp = timeStamp;
			boneData.rotations.push_back(data);
		}

		boneData.numScalings = p_channel->mNumScalingKeys;
		for (int scaleIndex = 0; scaleIndex < boneData.numScalings; ++scaleIndex)
		{
			aiVector3D scale = p_channel->mScalingKeys[scaleIndex].mValue;
			float timeStamp = static_cast<float>(p_channel->mScalingKeys[scaleIndex].mTime);
			DataStructure::Animation::KeyScale data;
			data.scale = GetMyVector3(scale);
			data.timeStamp = timeStamp;
			boneData.scales.push_back(data);
		}

		return boneData;
	}

	void ReadMissingBones(const aiAnimation* p_animation, DataStructure::Animation::Rig* p_rig, DataStructure::Animation::AnimationData& p_animationData)
	{
		int size = p_animation->mNumChannels;

		std::map<std::string, DataStructure::Animation::BoneInfo>& boneInfoMap = p_rig->boneInfos;
		int& boneCount = p_rig->boneCounter;

		for (int i = 0; i < size; i++)
		{
			aiNodeAnim* channel = p_animation->mChannels[i];
			std::string boneName = channel->mNodeName.data;

			if (boneInfoMap.find(boneName) == boneInfoMap.end())
			{
				boneInfoMap[boneName].id = boneCount;
				boneCount++;
			}
			p_animationData.bones.push_back(DataStructure::Animation::Bone(channel->mNodeName.data, boneInfoMap[channel->mNodeName.data].id, GetBoneData(channel)));
		}

		p_animationData.boneInfoMap = boneInfoMap;
	}

	void ReadHierarchyData(DataStructure::Animation::NodeData& p_dest, const aiNode* p_src)
	{
		assert(p_src);

		p_dest.name = p_src->mName.data;
		p_dest.transformation = GetMyMat4(p_src->mTransformation);
		p_dest.childrenCount = p_src->mNumChildren;

		for (unsigned int i = 0; i < p_src->mNumChildren; i++)
		{
			DataStructure::Animation::NodeData newData;
			ReadHierarchyData(newData, p_src->mChildren[i]);
			p_dest.children.push_back(newData);
		}
	}

	void SetVertexBoneDataToDefault(Vertex& p_vertex)
	{
		for (int i = 0; i < MAX_BONE_INFLUENCE; i++)
		{
			p_vertex.boneIDs[i] = -1;
			p_vertex.weights[i] = 0.0f;
		}
	}

	void SetVertexBoneData(Vertex& p_vertex, int p_boneID, float p_weight)
	{
		for (int i = 0; i < MAX_BONE_INFLUENCE; ++i)
		{
			if (p_vertex.boneIDs[i] < 0)
			{
				p_vertex.weights[i] = p_weight;
				p_vertex.boneIDs[i] = p_boneID;
				break;
			}
		}
	}

	void ExtractBoneWeightForVertices(std::vector<Vertex>& p_vertices, aiMesh* p_mesh, DataStructure::Animation::Rig* p_rig)
	{
		std::map<std::string, DataStructure::Animation::BoneInfo>& boneInfoMap = p_rig->boneInfos;
		int& boneCount = p_rig->boneCounter;

		for (unsigned int boneIndex = 0; boneIndex < p_mesh->mNumBones; ++boneIndex)
		{
			int boneID = -1;
			std::string boneName = p_mesh->mBones[boneIndex]->mName.C_Str();
			if (boneInfoMap.find(boneName) == boneInfoMap.end())
			{
				DataStructure::Animation::BoneInfo newBoneInfo;
				newBoneInfo.id = boneCount;
				newBoneInfo.offset = GetMyMat4(p_mesh->mBones[boneIndex]->mOffsetMatrix);
				boneInfoMap[boneName] = newBoneInfo;
				boneID = boneCount;
				boneCount++;
			}
			else
			{
				boneID = boneInfoMap[boneName].id;
			}
			assert(boneID != -1);
			auto weights = p_mesh->mBones[boneIndex]->mWeights;
			int numWeights = p_mesh->mBones[boneIndex]->mNumWeights;

			for (int weightIndex = 0; weightIndex < numWeights; ++weightIndex)
			{
				int vertexId = weights[weightIndex].mVertexId;
				float weight = weights[weightIndex].mWeight;
				assert(vertexId <= p_vertices.size());
				SetVertexBoneData(p_vertices[vertexId], boneID, weight);
			}
		}
	}

	std::vector<Resource::Texture> LoadMaterialTextures(aiMaterial* p_mat, aiTextureType p_type, std::string p_typeName, const std::string& p_directory)
	{
		std::vector<Resource::Texture> textures;
		for (unsigned int i = 0; i < p_mat->GetTextureCount(p_type); i++)
		{
			aiString str;
			p_mat->GetTexture(p_type, i, &str);

			Resource::Texture texture(-1, p_directory + "/" + str.C_Str(), "");
			texture.SetType(p_typeName);
			texture.SetPath(p_directory + "/" + str.C_Str());
			textures.push_back(texture);
		}
		return textures;
	}

	Resource::Mesh ProcessMesh(aiMesh* p_mesh, const aiScene* p_scene, const std::string& p_directory, DataStructure::Animation::Rig* p_rig)
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Resource::Texture> textures;
		DataStructure::Animation::MeshData meshData;

		for (unsigned int i = 0; i < p_mesh->mNumVertices; i++)
		{
			Vertex vertex;
			SetVertexBoneDataToDefault(vertex);
			vertex.position = GetMyVector3(p_mesh->mVertices[i]);
			vertex.normal = GetMyVector3(p_mesh->mNormals[i]);

			if (p_mesh->mTextureCoords[0])
			{
				Math::Vector2 vec;
				vec.x = p_mesh->mTextureCoords[0][i].x;
				vec.y = p_mesh->mTextureCoords[0][i].y;
				vertex.uv = vec;
			}
			else
			{
				vertex.uv = Math::Vector2(0.0f, 0.0f);
			}

			vertices.push_back(vertex);
		}
		for (unsigned int i = 0; i < p_mesh->mNumFaces; i++)
		{
			aiFace face = p_mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}
		aiMaterial* material = p_scene->mMaterials[p_mesh->mMaterialIndex];

		std::vector<Resource::Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", p_directory);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<Resource::Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", p_directory);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		std::vector<Resource::Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal", p_directory);
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		std::vector<Resource::Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height", p_directory);
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

		meshData.textures_loaded = textures;

		ExtractBoneWeightForVertices(vertices, p_mesh, p_rig);

		meshData.vertexBuffer = vertices;
		meshData.indexBuffer = indices;

		Resource::Mesh mesh(-1, p_mesh->mName.data, "");
		mesh.CopyMesh(meshData);
		return mesh;
	}

	void ProcessNode(aiNode* p_node, const aiScene* p_scene, DataStructure::Animation::MeshData& p_meshData, DataStructure::Animation::Rig* p_rig)
	{
		for (unsigned int i = 0; i < p_node->mNumMeshes; i++)
		{
			aiMesh* mesh = p_scene->mMeshes[p_node->mMeshes[i]];
			Resource::Mesh myMesh= ProcessMesh(mesh, p_scene, p_meshData.directory, p_rig);
			p_meshData.meshes.push_back(myMesh);
		}
		for (unsigned int i = 0; i < p_node->mNumChildren; i++)
		{
			ProcessNode(p_node->mChildren[i], p_scene, p_meshData, p_rig);
		}

	}

	
#pragma endregion UTILITY

	// ---------------------------------------
	//               Loader3D
	// ---------------------------------------

	const DataStructure::Animation::MeshData ProcessModel(std::string const& p_path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(p_path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace | aiProcess_FlipUVs);
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			Assertion(scene, importer.GetErrorString());
		}

		DataStructure::Animation::MeshData meshData;

		meshData.directory = p_path.substr(0, p_path.find_last_of('/'));

		DataStructure::Animation::Rig* rig = new DataStructure::Animation::Rig();
		rig->path = p_path;

		ProcessNode(scene->mRootNode, scene, meshData, rig);

		Core::AnimationManager::Get()->AddRig(rig);
		return meshData;
	}

	const DataStructure::Animation::AnimationData ProcessAnimation(const std::string& p_animationPath, DataStructure::Animation::Rig* p_rig)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(p_animationPath, aiProcess_Triangulate | aiProcess_FlipUVs);
		assert(scene && scene->mRootNode);
		aiAnimation* animation = scene->mAnimations[0];

		DataStructure::Animation::AnimationData animationData;
		animationData.duration = static_cast<float>(animation->mDuration);
		animationData.ticksPerSecond = static_cast<int>(animation->mTicksPerSecond);
		ReadHierarchyData(animationData.rootNode, scene->mRootNode);
		ReadMissingBones(animation, p_rig, animationData);
		return animationData;
	}
}
