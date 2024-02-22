#pragma once

#include <filesystem>
#include <Resource/Texture.hpp>
#include <Core/Engine.hpp>

namespace UI
{
	class Assets
	{
		// Attributes
	public:
		float padding;
		float thumbnailSize;
	
	private:
		const std::filesystem::path ASSETS_PATH;

		std::filesystem::path currentDirectory;

		Resource::Texture* iconDirectory;
		Resource::Texture* iconFile;

		// Methods
	public:
		Assets();

		void Draw(Core::Engine& p_engine);
		std::filesystem::path GetDirectoryPath() { return currentDirectory; };

	private:
		void ReturnButton();
		void AssetFile(Core::Engine& p_engine);
		void DirectoryFile(const std::filesystem::directory_entry& p_directory, const std::filesystem::path& p_path);
		void SceneFile(std::filesystem::path p_path, Core::Engine& p_engine);
		void ModelFile(std::filesystem::path p_path, Core::Engine& p_engine);
	};
}
