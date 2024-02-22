#pragma once

#include <string>

namespace Wrapper
{
	//Methods
	unsigned char* LoadTexture(const std::string& p_path, int* p_witdh, int* p_height, int* p_channels);
	void ReleaseTexture(unsigned char* p_data);
}