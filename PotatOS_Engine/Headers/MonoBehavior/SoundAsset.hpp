#pragma once

#include <MonoBehavior/IComponent.hpp>
#include <Wrapper/RHI.hpp>
#include <Core/ResourceManager.hpp>

namespace MonoBehavior
{
	class POTATOS_ENGINE_API SoundAsset : public IComponent
	{
	private:
		Wrapper::RHI* rhi;
		Resource::Shader* shader = nullptr;
		unsigned int VBO, VAO, textID;

		
		Math::Mat4 camMat;

	public:
		SoundAsset();

		void Draw(const MonoBehavior::Renderer::Camera* p_camera, const DataStructure::LightManager& p_lightManager,
			const MonoBehavior::Renderer::Light* p_light = nullptr) const override;

	};
}
