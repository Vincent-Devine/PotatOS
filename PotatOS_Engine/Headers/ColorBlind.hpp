#pragma once

namespace Math
{
	class Mat4;
}

namespace ColorVisionDeficiency
{
	enum class VISION_TYPE : unsigned int
	{
		NORMAL,
		PROTANOPIA,
		PROTANOMALY,
		DEUTERANOPIA,
		DEUTERANOMALY,
		TRITANOPIA,
		TRITANOMALY,
		BLUE_CONE_MONOCHROMACY,
		ACHROMATOPSIA
	};

	Math::Mat4 ColorMatrix(VISION_TYPE p_type);
}