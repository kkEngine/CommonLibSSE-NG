#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkVector4.h"
#include "RE/H/hkbVariableValue.h"

namespace RE
{
	class hkbVariableValueSet : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbVariableValueSet;

		// override (hkReferencedObject)
		~hkbVariableValueSet() override;  // 00

		hkArray<hkbVariableValue>    wordVariableValues;     // 10
		hkArray<hkVector4>           quadVariableValues;     // 20
		hkArray<hkReferencedObject*> variantVariableValues;  // 30
	};
	static_assert(sizeof(hkbVariableValueSet) == 0x40);
}
