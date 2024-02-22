#include "pch.h"

#include <ColorBlind.hpp>
#include <Math/Mat4.hpp>

namespace ColorVisionDeficiency
{
	Math::Mat4 ColorMatrix(VISION_TYPE p_type)
	{
		switch (p_type)
		{
		case ColorVisionDeficiency::VISION_TYPE::NORMAL:
			return Math::Mat4::Identity();
		case ColorVisionDeficiency::VISION_TYPE::PROTANOPIA:
			return Math::Mat4
			(
				0.56667f, 0.43333f, 0.f, 0.f,
				0.55833f, 0.44167f, 0.f, 0.f,
				0.f, 0.24167f, 0.75833f, 0.f,
				0.f, 0.f, 0.f, 1.f
			);
		case ColorVisionDeficiency::VISION_TYPE::PROTANOMALY:
			return Math::Mat4
			(
				0.81667f, 0.18333f, 0.f, 0.f,
				0.33333f, 0.66667f, 0.f, 0.f,
				0.f, 0.125f, 0.875f, 0.f,
				0.f, 0.f, 0.f, 1.f
			);
		case ColorVisionDeficiency::VISION_TYPE::DEUTERANOPIA:
			return Math::Mat4
			(
				0.625f, 0.375f, 0.f, 0.f,
				0.f, 0.7f, 0.3f, 0.f,
				0.f, 0.3f, 0.7f, 0.f,
				0.f, 0.f, 0.f, 1.f
			);
		case ColorVisionDeficiency::VISION_TYPE::DEUTERANOMALY:
			return Math::Mat4
			(
				0.8f, 0.2f, 0.f, 0.f,
				0.f, 0.25833f, 0.74167f, 0.f,
				0.f, 0.14167f, 0.85833f, 0.f,
				0.f, 0.f, 0.f, 1.f
			);
		case ColorVisionDeficiency::VISION_TYPE::TRITANOPIA:
			return Math::Mat4
			(
				0.95f, 0.05f, 0.f, 0.f,
				0.f, 0.4333f, 0.56667f, 0.f,
				0.f, 0.475f, 0.525f, 0.f,
				0.f, 0.f, 0.f, 1.f
			);
		case ColorVisionDeficiency::VISION_TYPE::TRITANOMALY:
			return Math::Mat4
			(
				0.96667f, 0.3333f, 0.f, 0.f,
				0.f, 0.7333f, 0.26667f, 0.f,
				0.f, 0.18333f, 0.81667f, 0.f,
				0.f, 0.f, 0.f, 1.f
			);
		case ColorVisionDeficiency::VISION_TYPE::BLUE_CONE_MONOCHROMACY:
			return Math::Mat4
			(
				0.1f, 0.1f, 0.1f, 0.f,
				0.1f, 0.1f, 0.1f, 0.f,
				0.05f, 0.05f, 0.9f, 0.f,
				0.f, 0.f, 0.f, 1.f
			);
		case ColorVisionDeficiency::VISION_TYPE::ACHROMATOPSIA:
			return Math::Mat4
			(
				0.299f, 0.587f, 0.114f, 0.f,
				0.299f, 0.587f, 0.114f, 0.f,
				0.299f, 0.587f, 0.114f, 0.f,
				0.f, 0.f, 0.f, 1.f
			);
		default:
			return Math::Mat4();
		}
	}
}