#include "pch.h"

#include <DataStructure/LightManager.hpp>

#include <DebugSystem/Assertion.hpp>
#include <Wrapper/RHI.hpp>

namespace DataStructure
{
	void LightManager::Draw(const int p_shaderProgram, const Math::Vector3& p_camPosition) const
	{
		Wrapper::RHI::UseShader(p_shaderProgram);

		Wrapper::RHI::SetFloatShader(p_shaderProgram, "nbDirectionalLight", static_cast<float>(directionalLights.size()));
		Wrapper::RHI::SetFloatShader(p_shaderProgram, "nbPointLight", static_cast<float>(pointLights.size()));
		Wrapper::RHI::SetFloatShader(p_shaderProgram, "nbSpotLight", static_cast<float>(spotLights.size()));

		BindShadowMaps();

		for (unsigned int i = 0; i < directionalLights.size(); i++)
		{
			directionalLights[i]->DrawLight(p_shaderProgram, p_camPosition, i);
		}

		for (unsigned int i = 0; i < spotLights.size(); i++)
		{
			spotLights[i]->DrawLight(p_shaderProgram, p_camPosition, i);
		}

		for (unsigned int i = 0; i < pointLights.size(); i++)
		{
			pointLights[i]->DrawLight(p_shaderProgram, p_camPosition, i);
		}
	}

	void LightManager::DrawDirectionalShadow(const int p_lightId) const
	{
		directionalLights[p_lightId]->DrawShadow();
	}

	void LightManager::DrawSpotShadow(const int p_lightId) const
	{
		spotLights[p_lightId]->DrawShadow();
	}

	void LightManager::BindShadowMaps() const
	{
		for (MonoBehavior::Renderer::DirectionalLight* dirLight : directionalLights)
		{
			Wrapper::RHI::BindShadowTexture(dirLight->GetShadowMap(), dirLight->GetID());
		}
		for (MonoBehavior::Renderer::SpotLight* spotLight : spotLights)
		{
			Wrapper::RHI::BindShadowTexture(spotLight->GetShadowMap(), spotLight->GetID());
		}
	}

	void LightManager::AddDirectionLight(MonoBehavior::Renderer::DirectionalLight* p_light)
	{
		if (directionalLights.size() >= MAX_DIRECTIONAL_LIGHT)
		{
			Log::Print("Can't add more direction light, there are already " + std::to_string(MAX_DIRECTIONAL_LIGHT) + " of them", LOG_LEVEL_TYPE::Warning);
			return;
		}
		directionalLights.push_back(p_light);
		Log::Print("Add direction light", LOG_LEVEL_TYPE::Notification);
	}

	void LightManager::AddPointLight(MonoBehavior::Renderer::PointLight* p_light)
	{
		if (pointLights.size() >= MAX_POINT_LIGHT)
		{
			Log::Print("Can't add more point light, there are already " + std::to_string(MAX_POINT_LIGHT) + " of them", LOG_LEVEL_TYPE::Warning);
			return;
		}
		pointLights.push_back(p_light);
		Log::Print("Add point light", LOG_LEVEL_TYPE::Notification);
	}

	void LightManager::AddSpotLight(MonoBehavior::Renderer::SpotLight* p_light)
	{
		if (spotLights.size() >= MAX_SPOT_LIGHT)
		{
			Log::Print("Can't add more spot light, there are already " + std::to_string(MAX_SPOT_LIGHT) + " of them", LOG_LEVEL_TYPE::Warning);
			return;
		}
		spotLights.push_back(p_light);
		Log::Print("Add spot light", LOG_LEVEL_TYPE::Notification);
	}
}
