
#include <freetype-2.13.0/include/ft2build.h>
#include FT_FREETYPE_H  

#include <Math/Vector2.hpp>
#include <Resource/Shader.hpp>
#include <map>
#include <glad.h>

namespace Wrapper
{
	struct Character 
	{
		unsigned int textureID;  // ID handle of the glyph texture
		Math::Vector2 size;      // Size of glyph
		Math::Vector2 bearing; // Offset from baseline to left/top of glyph
		unsigned int advance;    // Offset to advance to next glyph
	};

	class FontRenderer
	{
	public:
		std::map<GLchar, Character> characters;
	private:
		FT_Library ft;
		FT_Face face;

	public:
		FontRenderer();
	private :

	};
}