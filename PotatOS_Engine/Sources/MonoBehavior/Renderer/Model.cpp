#include "pch.h"

#include <MonoBehavior/Renderer/Model.hpp>
#include <MonoBehavior/Renderer/Camera.hpp>
#include <DataStructure/LightManager.hpp>
#include <Core/ResourceManager.hpp>
#include <Wrapper/RHI.hpp>

namespace MonoBehavior::Renderer
{
	Model::Model(Resource::Mesh* p_mesh, Resource::Shader* p_shader, Resource::Texture* p_texture)
		: shader(p_shader) 
		, texture(p_texture)
		, mesh(p_mesh)
	{
		componentType = MODEL;
	}

	void Model::Draw(const MonoBehavior::Renderer::Camera* p_camera, const DataStructure::LightManager& p_lightManager, const MonoBehavior::Renderer::Light* p_light) const
	{
		if (shader)
		{
			if (p_light)
			{
				Resource::Shader* shadowShader = p_light->GetShadowShader();
				shadowShader->Use();
				shadowShader->SetMat4("lightSpaceMatrix", p_light->GetSpaceMatrix());
				shadowShader->SetMat4("model", gameObject->transform.GetWorldMatrix());
				shadowShader->SetBool("isAnimated", gameObject->GetAnimator() != nullptr);
			}
			else
			{
				shader->Use();
				shader->SetMat4("view", p_camera->GetView());
				shader->SetMat4("projection", p_camera->GetProjection());
				if (texture)
				{
					texture->Draw(*shader->GetShaderProgram());
				}
				if (shader->GetIsFinishToInit())
				{
					p_lightManager.Draw(*shader->GetShaderProgram(), p_camera->gameObject->transform.GetPosition());
				}
				shader->SetMat4("model", gameObject->transform.GetWorldMatrix());
				Wrapper::RHI::Get()->ColorVisionDeficiencyFilter(*shader->GetShaderProgram());
			}
			mesh->Draw(*shader->GetShaderProgram(), p_light == nullptr);
		}
	}

	void Model::Destroy()
	{
		Core::ResourceManager* resourceManager = Core::ResourceManager::Get();

		resourceManager->StopUsedResource(shader);
		resourceManager->StopUsedResource(mesh);
		
		if (texture)
		{
			resourceManager->StopUsedResource(texture);
		}
	}
}
