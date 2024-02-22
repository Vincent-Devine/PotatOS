#include "pch.h"

#include <Resource/Mesh.hpp>
#include <Wrapper/Loader3D.hpp>
#include <Wrapper/RHI.hpp>
#include <DebugSystem/Log.hpp>
#include <Core/AnimationManager.hpp>

namespace Resource
{
	Mesh::Mesh(const int p_id, const std::string& p_path, const std::string& p_path2)
	{
		usedBy = 0;
		path = p_path;
		id = p_id;
		isFinishToInit = false;
		CreateName();
	}

	Mesh::Mesh(const Mesh& p_mesh)
	{
		usedBy = 0;
		path = p_mesh.path;
		id = p_mesh.id;
		isFinishToInit = false;
		name = p_mesh.name;
		VBO = p_mesh.VBO;
		VAO = p_mesh.VAO;
		EBO = p_mesh.EBO;
		vertexBuffer = p_mesh.vertexBuffer;
		indexBuffer = p_mesh.indexBuffer;
		textures = p_mesh.textures;
		subMeshes = p_mesh.subMeshes;
	}
	
	Mesh::Mesh()
	{
		name = "subMesh";
		isFinishToInit = false;
	}

	const bool Mesh::Init()
	{
		DataStructure::Animation::MeshData meshData = Wrapper::ProcessModel(path);
		CopyMesh(meshData);

		for (Mesh& subMeshe : subMeshes)
		{
			InitTexture(&subMeshe);
		}

		return true;
	}

	const bool Mesh::InitRHI()
	{
		for (Mesh& subMeshe : subMeshes)
		{
			Wrapper::RHI::InitMesh(subMeshe.VBO, subMeshe.VAO, subMeshe.EBO, subMeshe.vertexBuffer, subMeshe.indexBuffer, subMeshe.name);
			InitTextureRHI(&subMeshe);
		}

		FinishInit();
		return true;
	}

	void Mesh::Unload()
	{
		for (Mesh& subMesh : subMeshes)
		{
			Wrapper::RHI::DestroyMesh(subMesh.VBO, subMesh.VAO, subMesh.EBO);
		}
	}

	void Mesh::Draw(const unsigned int p_shaderProgram, const bool p_drawTexture) const
	{
		if (!isFinishToInit)
		{
			return;
		}
		for (const Mesh& subMeshe : subMeshes)
		{
			if (p_drawTexture)
			{
				DrawTexture(&subMeshe, p_shaderProgram);
			}
			Wrapper::RHI::DrawMesh(subMeshe.VAO, subMeshe.indexBuffer);
		}
	}

	void Mesh::CopyMesh(const DataStructure::Animation::MeshData& p_meshData)
	{
		subMeshes = p_meshData.meshes;
		textures = p_meshData.textures_loaded;
		vertexBuffer = p_meshData.vertexBuffer;
		indexBuffer = p_meshData.indexBuffer;
	}

	void Mesh::InitTexture(Mesh* p_mesh)
	{
		for (Texture& texture : p_mesh->textures)
		{
			texture.Init();
		}
	}

	void Mesh::InitTextureRHI(Mesh* p_mesh)
	{
		for (Texture& texture : p_mesh->textures)
		{
			texture.InitRHI();
		}
	}

	void Mesh::DrawTexture(const Mesh* p_mesh, const unsigned int p_shaderProgram) const
	{
		for (const Texture& texture : p_mesh->textures)
		{
			texture.Draw(p_shaderProgram);
		}
	}

	void Mesh::FinishInit()
	{
		isFinishToInit = true;
		for (Mesh& subMesh : subMeshes)
		{
			subMesh.isFinishToInit = true;
		}
	}
}
