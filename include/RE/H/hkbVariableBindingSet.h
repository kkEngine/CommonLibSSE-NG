#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkStringPtr.h"

namespace RE
{
	class hkClass;

	class hkbVariableBindingSet : public hkReferencedObject
	{
	public:
		struct Binding
		{
			enum class BindingType
			{
				BINDING_TYPE_VARIABLE = 0,
				BINDING_TYPE_CHARACTER_PROPERTY = 1,
			};

			enum class InternalBindingFlags
			{
				FLAG_NONE = 0,
				FLAG_OUTPUT = 1,
			};

			// Properties
			hkStringPtr                                    memberPath;             // 00
			const hkClass*                                 memberClass;            // 08
			int32_t                                        offsetInObjectPlusOne;  // 10
			int32_t                                        offsetInArrayPlusOne;   // 14
			int32_t                                        rootVariableIndex;      // 18
			int32_t                                        variableIndex;          // 1C
			int8_t                                         bitIndex;               // 20
			stl::enumeration<BindingType, int8_t>          bindingType;            // 21
			uint8_t                                        memberType;             // 22
			int8_t                                         variableType;           // 23
			stl::enumeration<InternalBindingFlags, int8_t> flags;                  // 24
		};
		static_assert(sizeof(Binding) == 0x28);

		inline static constexpr auto RTTI = RTTI_hkbVariableBindingSet;

		~hkbVariableBindingSet() override;  // 00

		// Properties
		hkArray<Binding> bindings;                // 10
		int32_t          indexOfBindingToEnable;  // 20
		bool             hasOutputBinding;        // 24
	};
	static_assert(sizeof(hkbVariableBindingSet) == 0x28);
}
