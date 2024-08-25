#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkPointerMap.h"
#include "RE/H/hkReferencedObject.h"

namespace RE
{
	class hkbSymbolIdMap : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbSymbolIdMap;

		hkArray<int>           internalToExternalMap;  // 10
		hkPointerMap<int, int> externalToInternalMap;  // 20
	};
	static_assert(sizeof(hkbSymbolIdMap) == 0x30);
}
