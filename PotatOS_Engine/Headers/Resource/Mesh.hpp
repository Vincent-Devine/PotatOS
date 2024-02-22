#pragma once

#include <DLLInclude.hpp>

#include <vector>
#include <map>

#include <Resource/IResource.hpp>
#include <Resource/Texture.hpp>
#include <Math/Mat4.inl>
#include <DataStructure/Animation/AnimData.hpp>
#include <Common.hpp>

#include <Refureku/Refureku.h>
#include <Refureku/Generated/Mesh.rfkh.h>

namespace Resource RFKNamespace()
{
	class RFKClass() POTATOS_ENGINE_API Mesh : public IResource
	{
	// Attributes
	private:
		unsigned int VBO, VAO, EBO;
		std::vector<Vertex> vertexBuffer;
		std::vector<unsigned int> indexBuffer;

		std::vector<Texture> textures;
		std::vector<Mesh> subMeshes;

	// Methods
	public:
		Mesh(const int p_id, const std::string& p_path, const std::string& p_path2 = "");
		Mesh(const Mesh& p_mesh);
		Mesh();

		const bool Init() override;
		const bool InitRHI() override;

		void Unload() override;

		void Draw(const unsigned int p_shaderProgram, const bool p_drawTexture = true) const;

		void CopyMesh(const DataStructure::Animation::MeshData& p_meshData);
		Mesh& GetSubMesh(const unsigned int p_index) { return subMeshes[p_index]; };
		std::vector<Mesh>& GetSubMeshes() { return subMeshes; };
	
	private:
		void InitTexture(Mesh* p_mesh);
		void InitTextureRHI(Mesh* p_mesh);
		void DrawTexture(const Mesh* p_mesh, const unsigned int p_shaderProgram) const;

		void FinishInit();

		Resource_Mesh_GENERATED
	};
}
File_Mesh_GENERATED