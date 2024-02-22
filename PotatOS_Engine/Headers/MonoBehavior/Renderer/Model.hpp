#pragma once

#include <DLLInclude.hpp>
#include <Resource/Shader.hpp>
#include <Resource/Texture.hpp>
#include <Resource/Mesh.hpp>
#include <Math/Mat4.inl>
#include <MonoBehavior/IComponent.hpp>

#include <Refureku/Refureku.h>
#include <Refureku/Generated/Model.rfkh.h>

namespace MonoBehavior::Renderer RFKNamespace()
{
	class RFKClass() POTATOS_ENGINE_API Model : public IComponent
	{
	// Attributes
	private:
		RFKField()
		Resource::Shader* shader;

		RFKField()
		Resource::Texture* texture;

		RFKField()
		Resource::Mesh* mesh;

	// Methods
	public:
		Model(Resource::Mesh* p_mesh, Resource::Shader* p_shader, Resource::Texture* p_texture);

		void Draw(const Camera* p_camera, const DataStructure::LightManager& p_lightManager, const MonoBehavior::Renderer::Light* p_light = nullptr) const override;
		void Destroy() override;

		const unsigned int GetShaderProgram() const { return *shader->GetShaderProgram(); };
		const Resource::Shader* GetShader() const { return shader; };
		const Resource::Mesh* GetMesh() const { return mesh; };
		const Resource::Texture* GetTexture() const { return texture; };

		MonoBehavior_Renderer_Model_GENERATED
	};
}

File_Model_GENERATED