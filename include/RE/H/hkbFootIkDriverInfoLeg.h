#pragma once

#include "RE/H/hkQuaternion.h"

namespace RE
{
	class hkbFootIkDriverInfoLeg
	{
	public:
		hkQuaternion prevAnkleRotLS;            // 00
		hkVector4    kneeAxisLS;                // 10
		hkVector4    footEndLS;                 // 20
		float        footPlantedAnkleHeightMS;  // 30
		float        footRaisedAnkleHeightMS;   // 34
		float        maxAnkleHeightMS;          // 38
		float        minAnkleHeightMS;          // 3C
		float        maxKneeAngleDegrees;       // 40
		float        minKneeAngleDegrees;       // 44
		float        maxAnkleAngleDegrees;      // 48
		std::int16_t hipIndex;                  // 4C
		std::int16_t kneeIndex;                 // 4E
		std::int16_t ankleIndex;                // 50
	};
	static_assert(sizeof(hkbFootIkDriverInfoLeg) == 0x60);
}
