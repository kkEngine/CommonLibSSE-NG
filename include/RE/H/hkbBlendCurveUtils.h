#pragma once

namespace RE
{
	class hkbBlendCurveUtils
	{
	public:
		enum class BlendCurve
		{
			BLEND_CURVE_SMOOTH = 0,
			BLEND_CURVE_LINEAR = 1,
			BLEND_CURVE_LINEAR_TO_SMOOTH = 2,
			BLEND_CURVE_SMOOTH_TO_LINEAR = 3,
		};
	};
}
