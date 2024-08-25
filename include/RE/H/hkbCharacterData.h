#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkbCharacterDataCharacterControllerInfo.h"
#include "RE/Offsets_RTTI.h"

namespace RE
{
	class hkbCharacterStringData;
	class hkbFootIkDriverInfo;
	class hkbHandIkDriverInfo;
	class hkbMirroredSkeletonInfo;
	class hkbVariableInfo;
	class hkbVariableValueSet;

	class hkbCharacterData : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbCharacterData;
		inline static constexpr auto VTABLE = VTABLE_hkbCharacterData;

		~hkbCharacterData() override;  // 00

		hkbCharacterDataCharacterControllerInfo characterControllerInfo;  // 10
		hkVector4                               modelUpMS;                // 30
		hkVector4                               modelForwardMS;           // 40
		hkVector4                               modelRightMS;             // 50
		hkArray<hkbVariableInfo>                characterPropertyInfos;   // 60
		hkArray<std::int32_t>                   numBonesPerLod;           // 70
		hkRefPtr<hkbVariableValueSet>           characterPropertyValues;  // 80
		hkRefPtr<hkbFootIkDriverInfo>           footIkDriverInfo;         // 88
		hkRefPtr<hkbHandIkDriverInfo>           handIkDriverInfo;         // 90
		hkRefPtr<hkbCharacterStringData>        stringData;               // 98
		hkRefPtr<hkbMirroredSkeletonInfo>       mirroredSkeletonInfo;     // A0
		float                                   scale;                    // A8
		std::int16_t                            numHands;                 // AC
		std::int16_t                            numFloatSlots;            // AE
	};
	static_assert(sizeof(hkbCharacterData) == 0xB0);
}
