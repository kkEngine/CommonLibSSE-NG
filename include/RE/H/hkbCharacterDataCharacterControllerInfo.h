#pragma once

#include "RE/H/hkRefPtr.h"

namespace RE
{
	class hkpCharacterControllerCinfo;

	class hkbCharacterDataCharacterControllerInfo
	{
	public:
		float                                 capsuleHeight;             // 00
		float                                 capsuleRadius;             // 04
		std::uint32_t                         collisionFilterInfo;       // 08
		hkRefPtr<hkpCharacterControllerCinfo> characterControllerCinfo;  // 10
	};
	static_assert(sizeof(hkbCharacterDataCharacterControllerInfo) == 0x18);
}
