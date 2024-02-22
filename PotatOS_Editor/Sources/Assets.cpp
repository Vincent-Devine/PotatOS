#include "Assets.hpp"

#include <ImGUI/Include/imgui.h>

#include <Core/ResourceManager.hpp>
#include <Wrapper/JsonLayer.hpp>

namespace UI
{
	Assets::Assets()
		: ASSETS_PATH("Resources")
		, currentDirectory(ASSETS_PATH)
		, padding(16.0f)
		, thumbnailSize(64.0f)
	{
		iconDirectory = Core::ResourceManager::Get()->UseTexture("UI_Assets/Icon/DirectoryIcon.png");
		iconFile = Core::ResourceManager::Get()->UseTexture("UI_Assets/Icon/FileIcon.png");
	}

	void Assets::Draw(Core::Engine& p_engine)
	{
		ImGui::Begin("Assets");

		ReturnButton();

		float cellsize = thumbnailSize + padding;
		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = static_cast<int>(panelWidth / cellsize);
		if (columnCount < 1)
		{
			columnCount = 1;
		}

		ImGui::Columns(columnCount, 0, false);
		
		AssetFile(p_engine);

		ImGui::Columns(1);
		ImGui::End();
	}

	void Assets::ReturnButton()
	{
		if (currentDirectory != std::filesystem::path(ASSETS_PATH))
		{
			if (ImGui::Button("<-"))
			{
				currentDirectory = currentDirectory.parent_path();
			}
		}
	}

	void Assets::AssetFile(Core::Engine& p_engine)
	{
		for (const std::filesystem::directory_entry& directoryEntry : std::filesystem::directory_iterator(currentDirectory))
		{
			const std::filesystem::path& path = directoryEntry.path();
			const std::filesystem::path relativePath = std::filesystem::relative(path, ASSETS_PATH);
			std::string filename = relativePath.filename().string();

			unsigned int icon;
			if (directoryEntry.is_directory())
			{
				icon = iconDirectory->GetIdText();
			}
			else
			{
				icon = iconFile->GetIdText();
			}

			ImGui::ImageButton((ImTextureID)icon, { thumbnailSize, thumbnailSize }, { 1, 0 }, { 0, 1 });
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				DirectoryFile(directoryEntry, path);
				SceneFile(relativePath, p_engine);
				ModelFile(relativePath, p_engine);
			}
			ImGui::TextWrapped(filename.c_str());
			ImGui::NextColumn();
		}
	}

	void Assets::DirectoryFile(const std::filesystem::directory_entry& p_directory, const std::filesystem::path& p_path)
	{
		if (p_directory.is_directory())
		{
			currentDirectory /= p_path.filename();
		}
	}

	void Assets::SceneFile(std::filesystem::path p_path, Core::Engine& p_engine)
	{
		if (p_path.extension() == ".json")
		{
			p_engine.ChangeScene(p_path.stem().string().c_str());
		}
	}

	void Assets::ModelFile(std::filesystem::path p_path, Core::Engine& p_engine)
	{
		if (p_path.extension() == ".md5mesh" || p_path.extension() == ".fbx" || p_path.extension() == ".dae" || p_path.extension() == ".obj")
		{
			p_engine.ChangePreview(p_path.string().c_str(), p_path.stem().string().c_str());
		}
	}
}
