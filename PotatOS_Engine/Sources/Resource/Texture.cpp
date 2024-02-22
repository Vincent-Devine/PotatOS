#include "pch.h"

#include <Resource/Texture.hpp>

#include <Wrapper/LoaderImage.hpp>
#include <Wrapper/RHI.hpp>

namespace Resource
{
	Texture::Texture(const int p_id, const std::string& p_path, const std::string& p_path2)
		: data()
		, witdh(0)
		, height(0)
		, channels(0)
		, idText(0)
		, type("")
	{
		usedBy = 0;
		path = p_path;
		id = p_id;
		name = "";
		CreateName();
	}

	Texture::Texture(const Texture& p_texture)
		: data()
		, witdh(p_texture.witdh)
		, height(p_texture.height)
		, channels(p_texture.channels)
		, idText(p_texture.idText)
		, type(p_texture.type)
	{
		usedBy = 0;
		path = p_texture.path;
		id = p_texture.id;
		name = p_texture.name;
	}

	const bool Texture::Init()
	{
		isFinishToInit = false;

		data = Wrapper::LoadTexture(path, &witdh, &height, &channels);
		
		return true;
	}

	const bool Texture::InitRHI()
	{
		Wrapper::RHI::InitTexture(idText, data, witdh, height, channels, path);
		Wrapper::ReleaseTexture(data);

		isFinishToInit = true;
		return true;
	}

	void Texture::Draw(const unsigned int p_shaderProgram) const
	{
		if (!isFinishToInit)
		{
			return;
		}

		Wrapper::RHI::DrawTexture(idText, p_shaderProgram);
	}
}