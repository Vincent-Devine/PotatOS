#pragma once

#include <DLLInclude.hpp>

#include <Resource/IResource.hpp>

#include <Refureku/Refureku.h>
#include <Refureku/Generated/Texture.rfkh.h>

namespace Resource RFKNamespace()
{
	class RFKClass() POTATOS_ENGINE_API Texture : public IResource
	{
	// Attributes
	private:
		int witdh, height, channels;
		unsigned char* data;
		unsigned int idText;
		std::string type;

	// Methods
	public:
		Texture(const int p_id, const std::string& p_path, const std::string& p_path2 = "");
		Texture(const Texture& p_texture);

		const bool Init() override;
		const bool InitRHI() override;
		void Draw(const unsigned int p_shaderProgram) const;

		unsigned int GetIdText() { return idText; };

		void SetPath(const std::string& p_path) { path = p_path; };
		void SetIdText(const unsigned int p_idText) { idText = p_idText; };
		void SetType(const std::string& p_type) { type = p_type; };

		Resource_Texture_GENERATED

	};
}

File_Texture_GENERATED
