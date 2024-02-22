#include "pch.h"
#include <filesystem>
#include <Resource/IResource.hpp>

namespace Resource
{
	void IResource::CreateName()
	{
		name = std::filesystem::path(path).filename().string();
	}
}
