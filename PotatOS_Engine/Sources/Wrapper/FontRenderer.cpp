#include "pch.h"

#include <Wrapper/FontRenderer.hpp>
#include <iostream>
#include <gl/GL.h>
#include <glad.h>
#include <GLFW/glfw3.h>

namespace Wrapper
{
	FontRenderer::FontRenderer()
	{
		if (FT_Init_FreeType(&ft))
		{
			std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
			return;
		}

        if (FT_New_Face(ft, "Resources/Fonts/Arial/arial.ttf", 0, &face)) {
            std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
            return ;
        }
        else 
        {
            // set size to load glyphs as
            FT_Set_Pixel_Sizes(face, 0, 48);

            // disable byte-alignment restriction
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            // load first 128 characters of ASCII set
            for (unsigned char c = 0; c < 128; c++)
            {
                // Load character glyph 
                if (FT_Load_Char(face, c, FT_LOAD_RENDER))
                {
                    std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                    continue;
                }
                // generate texture
                unsigned int texture;
                glGenTextures(1, &texture);
                glBindTexture(GL_TEXTURE_2D, texture);
                glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    GL_RED,
                    face->glyph->bitmap.width,
                    face->glyph->bitmap.rows,
                    0,
                    GL_RED,
                    GL_UNSIGNED_BYTE,
                    face->glyph->bitmap.buffer
                );
                // set texture options
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                // now store character for later use
                Character character = 
                {
                    texture,
                    Math::Vector2((float)face->glyph->bitmap.width, (float)face->glyph->bitmap.rows),
                    Math::Vector2((float)face->glyph->bitmap_left, (float)face->glyph->bitmap_top),
                    static_cast<unsigned int>(face->glyph->advance.x)
                };
                characters.insert(std::pair<char, Character>(c, character));
            }
            glBindTexture(GL_TEXTURE_2D, 0);
        }
        // destroy FreeType once we're finished
        FT_Done_Face(face);
        FT_Done_FreeType(ft);

	}

}