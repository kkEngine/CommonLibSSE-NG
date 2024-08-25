#pragma once

#include "RE/H/hkReferencedObject.h"
#include "RE/Offsets_RTTI.h"

namespace RE
{
	class hkbFootIkDriverInfoLeg;

	class hkbFootIkDriverInfo : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbFootIkDriverInfo;

		~hkbFootIkDriverInfo() override;  // 00

		hkArray<hkbFootIkDriverInfoLeg> legs;                    // 10
		float                           raycastDistanceUp;       // 20
		float                           raycastDistanceDown;     // 24
		float                           originalGroundHeightMS;  // 28
		float                           verticalOffset;          // 2C
		std::uint32_t                   collisionFilterInfo;     // 30
		float                           forwardAlignFraction;    // 34
		float                           sidewaysAlignFraction;   // 38
		float                           sidewaysSampleWidth;     // 3C
		bool                            lockFeetWhenPlanted;     // 40
		bool                            useCharacterUpVector;    // 41
		bool                            isQuadrupedNarrow;       // 42
	};
	static_assert(sizeof(hkbFootIkDriverInfo) == 0x48);
}
