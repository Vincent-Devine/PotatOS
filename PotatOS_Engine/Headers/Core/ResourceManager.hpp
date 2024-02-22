#pragma once
#include <DLLInclude.hpp>

#include <unordered_map>
#include <iostream>

#include <Resource/IResource.hpp>
#include <Resource/Mesh.hpp>
#include <Resource/Texture.hpp>
#include <Resource/Shader.hpp>
#include <Resource/PrimitiveMesh.hpp>
#include <Resource/Sound.hpp>

namespace Core
{
	class POTATOS_ENGINE_API ResourceManager
	{
		// Attributes
	private:
		static ResourceManager* singleton;
		std::unordered_map<std::string, Resource::IResource*> resources;

		// Methods
	public:
		static ResourceManager* Get();

		Resource::Mesh* UseMesh(const std::string& p_path);
		Resource::Texture* UseTexture(const std::string& p_path);
		Resource::Shader* UseShader(const std::string& p_path, const std::string& p_path2);
		Resource::Sound* UseSound(const std::string& p_path);

		Resource::PrimitiveMesh* UsePrimitiveMesh(const std::string& p_name);

		void StopUsedResource(Resource::IResource* p_resource);

	private:
		Resource::Mesh* GetResourceMesh(const std::string& p_path) const;
		Resource::Texture* GetResourceTexture(const std::string& p_path) const;
		Resource::Shader* GetResourceShader(const std::string& p_path) const;
		Resource::PrimitiveMesh* GetResourcePrimitiveMesh(const std::string& p_name) const;
		Resource::Sound* GetResourceSound(const std::string& p_path) const;

		Resource::Mesh* CreateResourceMesh(const std::string& p_path);
		Resource::Texture* CreateResourceTexture(const std::string& p_path);
		Resource::Shader* CreateResourceShader(const std::string& p_path, const std::string& p_path2);
		Resource::Sound* CreateResourceSound(const std::string& p_path);
		Resource::PrimitiveMesh* CreateResourcePrimitiveMesh(const std::string& p_name);

		void LoadResource(Resource::IResource* p_resource);
		void DeleteResource(Resource::IResource* p_resource);
	};
}
