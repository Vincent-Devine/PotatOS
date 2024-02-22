#pragma once
#include <DLLInclude.hpp>

#include <Math/Vector3.hpp>
#include <Math/Vector4.hpp>
#include <MonoBehavior/IComponent.hpp>

#include <Resource/Shader.hpp>

#include <Refureku/Refureku.h>
#include <Refureku/Generated/Light.rfkh.h>

namespace MonoBehavior RFKNamespace()
{
	namespace Renderer RFKNamespace()
	{
		struct InitLight
		{
			Math::Vector4 ambient;
			Math::Vector4 diffuse;
			Math::Vector4 specular;
		};

		class RFKClass() POTATOS_ENGINE_API Light : public IComponent
		{
		// Attributes
		protected:

			RFKField()
			Math::Vector4 ambient;

			RFKField()
			Math::Vector4 diffuse;

			RFKField()
			Math::Vector4 specular;

			Math::Mat4 viewMatrix;
			Math::Mat4 projectionMatrix;
			unsigned int depthMap;
			unsigned int id;

		private:
			Resource::Shader* shadowShader = nullptr;
			unsigned int depthFBO;
			Math::Mat4 spaceMatrix;
			unsigned int shadowSize;
	
		// Methods
		public:
			virtual void DrawLight(const int p_shaderProgram, const Math::Vector3& p_cameraPosition, std::string& p_array) const;
			void DrawShadow();

			// IComponent
			void Start(GAMESTATE* p_gameState) override;
			void Update(const float p_deltaTime, const Inputs& p_inputs) override;

			const Math::Vector4& GetAmbient() const { return ambient; };
			const Math::Vector4& GetDiffuse() const { return diffuse; };
			const Math::Vector4& GetSpecular() const { return specular; };

			Math::Mat4 GetSpaceMatrix() const { return spaceMatrix; };

			Resource::Shader* GetShadowShader() const { return shadowShader; };
			unsigned int GetShadowMap() const { return depthMap; };
			unsigned int GetID() { return id; };
			
			MonoBehavior_Renderer_Light_GENERATED
		};
	}
}

File_Light_GENERATED
