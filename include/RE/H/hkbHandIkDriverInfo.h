#pragma once

#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkbBlendCurveUtils.h"
#include "RE/Offsets_RTTI.h"

namespace RE
{
	class hkbHandIkDriverInfoHand;

	class hkbHandIkDriverInfo : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbHandIkDriverInfo;

		~hkbHandIkDriverInfo() override;  // 00

		hkArray<hkbHandIkDriverInfoHand>                              hands;           // 10
		stl::enumeration<hkbBlendCurveUtils::BlendCurve, std::int8_t> fadeInOutCurve;  // 20
	};
	static_assert(sizeof(hkbHandIkDriverInfo) == 0x28);
}
