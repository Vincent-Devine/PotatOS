#include "pch.h"

#include <Core/ResourceManager.hpp>
#include <Core/ThreadPool.hpp>
#include <DebugSystem/Assertion.hpp>

namespace Core
{
	ResourceManager* ResourceManager::singleton = nullptr;

	ResourceManager* ResourceManager::Get()
	{
		if (singleton == nullptr)
		{
			singleton = new ResourceManager;
		}
		return singleton;
	}

	Resource::Mesh* ResourceManager::UseMesh(const std::string& p_path)
	{
		Resource::Mesh* resource = nullptr;
		resource = GetResourceMesh(p_path);

		if (resource == nullptr)
		{
			resource = CreateResourceMesh(p_path);
			LoadResource(resource);
		}

		resource->StartUsing();
		return resource;
	}

	Resource::Texture* ResourceManager::UseTexture(const std::string& p_path)
	{
		Resource::Texture* resource = nullptr;
		resource = GetResourceTexture(p_path);

		if (resource == nullptr)
		{
			resource = CreateResourceTexture(p_path);
			LoadResource(resource);

		}

		resource->StartUsing();
		return resource;
	}

	Resource::Shader* ResourceManager::UseShader(const std::string& p_path, const std::string& p_path2)
	{
		Resource::Shader* resource = nullptr;
		resource = GetResourceShader(p_path);

		if (resource == nullptr)
		{
			resource = CreateResourceShader(p_path, p_path2);
			LoadResource(resource);

		}

		resource->StartUsing();
		return resource;
	}

	Resource::PrimitiveMesh* ResourceManager::UsePrimitiveMesh(const std::string& p_name)
	{
		Resource::PrimitiveMesh* resource = nullptr;
		resource = GetResourcePrimitiveMesh(p_name);

		if (resource == nullptr)
		{
			resource = CreateResourcePrimitiveMesh(p_name);
			LoadResource(resource);
		}

		resource->StartUsing();
		return resource;
	}

	Resource::Sound* ResourceManager::UseSound(const std::string& p_path)
	{
		Resource::Sound* resource = nullptr;
		resource = GetResourceSound(p_path);

		if (resource == nullptr)
		{
			resource = CreateResourceSound(p_path);
			LoadResource(resource);
		}

		dynamic_cast<Resource::IResource*>(resource)->StartUsing();
		return resource;
	}

	void ResourceManager::StopUsedResource(Resource::IResource* p_resource)
	{
		p_resource->StopUsing();
		if (p_resource->GetUsedBy() == 0)
		{
			DeleteResource(p_resource);
		}
	}

	Resource::Mesh* ResourceManager::GetResourceMesh(const std::string& p_path) const
	{
		Resource::Mesh* resource = nullptr;

		if (resources.count(p_path) != 0)
		{
			resource = static_cast<Resource::Mesh*>(resources.find(p_path)->second);
		}

		return resource;
	}

	Resource::Texture* ResourceManager::GetResourceTexture(const std::string& p_path) const
	{
		Resource::Texture* resource = nullptr;

		if (resources.count(p_path) != 0)
		{
			resource = static_cast<Resource::Texture*>(resources.find(p_path)->second);
		}

		return resource;
	}

	Resource::Shader* ResourceManager::GetResourceShader(const std::string& p_path) const
	{
		Resource::Shader* resource = nullptr;

		if (resources.count(p_path) != 0)
		{
			resource = static_cast<Resource::Shader*>(resources.find(p_path)->second);
		}

		return resource;
	}

	Resource::Sound* ResourceManager::GetResourceSound(const std::string& p_path) const
	{

		Resource::Sound* resource = nullptr;

		if (resources.count(p_path) != 0)
		{
			resource = static_cast<Resource::Sound*>(resources.find(p_path)->second);
		}

		return resource;
	}

	Resource::PrimitiveMesh* ResourceManager::GetResourcePrimitiveMesh(const std::string& p_name) const
	{
		Resource::PrimitiveMesh* resource = nullptr;

		if (resources.count(p_name) != 0)
		{
			resource = static_cast<Resource::PrimitiveMesh*>(resources.find(p_name)->second);
		}

		return resource;
	}

	Resource::Mesh* ResourceManager::CreateResourceMesh(const std::string& p_path)
	{
		const size_t id = resources.size();
		auto [it, _] = resources.insert_or_assign(p_path, new Resource::Mesh(static_cast<int>(id), p_path));

		Log::Print("Add mesh " + p_path + " in Resource Manager", LOG_LEVEL_TYPE::Notification);
		return static_cast<Resource::Mesh*>(it->second);
	}

	Resource::Texture* ResourceManager::CreateResourceTexture(const std::string& p_path)
	{
		const size_t id = resources.size();
		auto [it, _] = resources.insert_or_assign(p_path, new Resource::Texture(static_cast<int>(id), p_path));

		Log::Print("Add texture " + p_path + " in Resource Manager", LOG_LEVEL_TYPE::Notification);
		return static_cast<Resource::Texture*>(it->second);
	}

	Resource::Shader* ResourceManager::CreateResourceShader(const std::string& p_path, const std::string& p_path2)
	{
		const size_t id = resources.size();
		auto [it, _] = resources.insert_or_assign(p_path, new Resource::Shader(static_cast<int>(id), p_path, p_path2));

		Log::Print("Add shader " + p_path + " in Resource Manager", LOG_LEVEL_TYPE::Notification);
		return static_cast<Resource::Shader*>(it->second);
	}

	Resource::Sound* ResourceManager::CreateResourceSound(const std::string& p_path)
	{
		const size_t id = resources.size();
		auto [it, _] = resources.insert_or_assign(p_path, new Resource::Sound(static_cast<int>(id), p_path));

		Log::Print("Add sound " + p_path + " in Resource Manager", LOG_LEVEL_TYPE::Notification);
		return static_cast<Resource::Sound*>(it->second);
	}

	Resource::PrimitiveMesh* ResourceManager::CreateResourcePrimitiveMesh(const std::string& p_name)
	{
		const size_t id = resources.size();
		auto [it, _] = resources.insert_or_assign(p_name, new Resource::PrimitiveMesh(static_cast<int>(id), p_name));

		Log::Print("Add primitive mesh " + p_name + " in Resource Manager", LOG_LEVEL_TYPE::Notification);
		return static_cast<Resource::PrimitiveMesh*>(it->second);
	}

	void ResourceManager::LoadResource(Resource::IResource* p_resource)
	{
		ThreadPool::Get()->AddResourceToInit(p_resource);
	}

	void ResourceManager::DeleteResource(Resource::IResource* p_resource)
	{
		Log::Print("Unload and Delete resource " + p_resource->GetName(), LOG_LEVEL_TYPE::Notification);
		p_resource->Unload();
		singleton->resources.erase(p_resource->GetPath());
		delete p_resource;
	}
}
