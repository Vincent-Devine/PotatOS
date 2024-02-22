#pragma once
#include <DLLInclude.hpp>
#include <filesystem>

#include <Resource/IResource.hpp>
#include <Wrapper/SoundLayer.hpp>

#include <Refureku/Refureku.h>
#include <Refureku/Generated/Sound.rfkh.h>

namespace Resource RFKNamespace()
{
	class RFKClass() POTATOS_ENGINE_API Sound : public IResource
	{
	public:
		int index;
		Sound(const unsigned int p_id, const std::string& p_path);
		Sound(Sound& p_sound);
		
		const bool Init() override;
		const bool InitRHI() override { return true; };

		void Unload() override {};

		Resource_Sound_GENERATED
	};
}
File_Sound_GENERATED
