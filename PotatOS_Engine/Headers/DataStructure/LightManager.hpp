#pragma once

#include <vector>

#include <MonoBehavior/Renderer/DirectionalLight.hpp>
#include <MonoBehavior/Renderer/PointLight.hpp>
#include <MonoBehavior/Renderer/SpotLight.hpp>

namespace DataStructure
{
	const unsigned int MAX_DIRECTIONAL_LIGHT = 5;
	const unsigned int MAX_POINT_LIGHT = 5;
	const unsigned int MAX_SPOT_LIGHT = 5;

	class LightManager
	{
	// Attributes
	private:
		std::vector<MonoBehavior::Renderer::DirectionalLight*>	directionalLights;
		std::vector<MonoBehavior::Renderer::PointLight*>		pointLights;
		std::vector<MonoBehavior::Renderer::SpotLight*>			spotLights;

	// Methods
	public:
		void Draw(const int p_shaderProgram, const Math::Vector3& p_camPosition) const;
		void DrawDirectionalShadow(const int p_lightId) const;
		void DrawSpotShadow(const int p_lightId) const;
		void BindShadowMaps() const;

		void AddDirectionLight(MonoBehavior::Renderer::DirectionalLight* p_light);
		void AddPointLight(MonoBehavior::Renderer::PointLight* p_light);
		void AddSpotLight(MonoBehavior::Renderer::SpotLight* p_light);

		unsigned int GetDirectionalLightSize() { return static_cast<unsigned int>(directionalLights.size()); };
		MonoBehavior::Renderer::Light* GetDirectionalLightAsLight(unsigned int p_lightId) { return directionalLights[p_lightId]; };
		unsigned int GetSpotLightSize() { return static_cast<unsigned int>(spotLights.size()); };
		MonoBehavior::Renderer::Light* GetSpotLightAsLight(unsigned int p_lightId) { return spotLights[p_lightId]; };
		void SetDirectionalPosition(const unsigned int p_id, const Math::Vector3& p_position) { directionalLights[p_id]->SetPosition(p_position); };
	};
}
