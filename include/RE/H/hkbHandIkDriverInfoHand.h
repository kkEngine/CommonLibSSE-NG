#pragma once

#include "RE/H/hkQuaternion.h"
#include "RE/H/hkStringPtr.h"

namespace RE
{
	class hkbHandIkDriverInfoHand
	{
	public:
		hkVector4    elbowAxisLS;             // 00
		hkVector4    backHandNormalLS;        // 10
		hkVector4    handOffsetLS;            // 20
		hkQuaternion handOrienationOffsetLS;  // 30
		float        maxElbowAngleDegrees;    // 40
		float        minElbowAngleDegrees;    // 44
		std::int16_t shoulderIndex;           // 48
		std::int16_t shoulderSiblingIndex;    // 4A
		std::int16_t elbowIndex;              // 4C
		std::int16_t elbowSiblingIndex;       // 4E
		std::int16_t wristIndex;              // 50
		bool         enforceEndPosition;      // 52
		bool         enforceEndRotation;      // 53
		hkStringPtr  localFrameName;          // 58
	};
	static_assert(sizeof(hkbHandIkDriverInfoHand) == 0x60);
}
