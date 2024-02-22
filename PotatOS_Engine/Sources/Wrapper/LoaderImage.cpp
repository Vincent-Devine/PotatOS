#include "pch.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <Wrapper/LoaderImage.hpp>
#include <DebugSystem/Assertion.hpp>
#include <iostream>

namespace Wrapper
{
	unsigned char* LoadTexture(const std::string& p_path, int* p_witdh, int* p_height, int* p_channels)
	{
		unsigned char* data = stbi_load(p_path.c_str(), p_witdh, p_height, p_channels, 0);
		//Assertion(data, "Failed to load texture.");
		return data;
	}

	unsigned char* LoadCubeMap(const std::string& p_path, int* p_witdh, int* p_height, int* p_channels)
	{
		unsigned char* image;
		const char* filenames[6] = 
		{
			"right.jpg", "left.jpg",
			"top.jpg", "bottom.jpg",
			"front.jpg", "back.jpg"
		};

		for (unsigned int i = 0; i < 6; ++i)
		{
			image = stbi_load(filenames[i], p_witdh, p_height, p_channels, 0);
			if (image)
			{
				//glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
				return image; 
			}
			else
			{
				std::cout << "Error";
			}
		}
	}

	void ReleaseTexture(unsigned char* p_data)
	{
		stbi_image_free(p_data);
	}
}