#include "pch.h"

#include <MonoBehavior/Renderer/Light.hpp>
#include <Wrapper/RHI.hpp>
#include <Core/ResourceManager.hpp>

namespace MonoBehavior::Renderer
{
	void Light::Start(GAMESTATE* p_gameState)
	{
		static unsigned int ID = 2U;
		id = ID;
		++ID;
		shadowShader = Core::ResourceManager::Get()->UseShader("Resources/Shaders/DepthMap.vert", "Resources/Shaders/DepthMap.frag");
		shadowSize = 4096U;
		Wrapper::RHI::InitDepthMap(&depthFBO, &depthMap, shadowSize);
	}

	void Light::DrawLight(const int p_shaderProgram, const Math::Vector3& p_camPosition, std::string& p_array) const
	{
		p_array += "lightData.";

		Wrapper::RHI::SetMat4Shader(p_shaderProgram, (p_array + "spaceMatrix").c_str(), spaceMatrix);

		Wrapper::RHI::SetVec4Shader(p_shaderProgram, (p_array + "ambient").c_str(), ambient);
		Wrapper::RHI::SetVec4Shader(p_shaderProgram, (p_array + "diffuse").c_str(), diffuse);
		Wrapper::RHI::SetVec4Shader(p_shaderProgram, (p_array + "specular").c_str(), specular);
		Wrapper::RHI::SetVec3Shader(p_shaderProgram, (p_array + "lightPosition").c_str(), gameObject->transform.GetPosition());
		Wrapper::RHI::SetVec3Shader(p_shaderProgram, (p_array + "viewPosition").c_str(), p_camPosition);
	}

	void Light::Update(const float p_deltaTime, const Inputs& p_inputs)
	{
		spaceMatrix = projectionMatrix * viewMatrix;
	}

	void Light::DrawShadow()
	{
		shadowShader->Use();
		Wrapper::RHI::BindDepthMap(shadowSize, depthFBO, depthMap);
	}
}
