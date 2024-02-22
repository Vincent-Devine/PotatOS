#pragma once

#include <DLLInclude.hpp>

#include <vector>

#include <Resource/IResource.hpp>
#include <Math/Vector3.hpp>

namespace Resource
{
	enum class COLLIDER_TYPE : unsigned int
	{
		BOX,
		PLANE,
		SPHERE,
		CAPSULE
	};

	class POTATOS_ENGINE_API PrimitiveMesh : public IResource
	{
	public:
		COLLIDER_TYPE type;

	private:
		unsigned int VBO, VAO, EBO;
		std::vector<Math::Vector3> vertexBuffer;
		std::vector<unsigned int> indexBuffer;

		// Methods
	public:
		PrimitiveMesh(const int p_id, const std::string& p_name);

		const bool Init() override;
		const bool InitRHI() override;

		void Unload() override;

		void Draw(const unsigned int p_shaderProgram) const;

		void InitCapsule(const float p_halfHeight = 0.5f, const float p_radius = 1.f);
	private:
		void InitPlane();
		void InitBox();
		void InitSphere();
	};
}
