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
			// Which data we are binding to.
			enum class BindingType
			{
				// Binding to a variable.
				BINDING_TYPE_VARIABLE = 0,

				// Binding to a character property.
				BINDING_TYPE_CHARACTER_PROPERTY = 1,
			};

			enum class InternalBindingFlags
			{
				FLAG_NONE = 0,

				// values are copied from the property to bound variables
				FLAG_OUTPUT = 1,
			};

			bool isOutput() const { return flags.all(InternalBindingFlags::FLAG_OUTPUT); };

			// Properties
			hkStringPtr                                    memberPath;                                         // 00
			hkClass*                                       memberClass{ nullptr };                             // 08
			int32_t                                        offsetInObjectPlusOne{ 0 };                         // 10
			int32_t                                        offsetInArrayPlusOne{ 0 };                          // 14
			int32_t                                        rootVariableIndex{ -1 };                            // 18
			int32_t                                        variableIndex{ 0 };                                 // 1C
			int8_t                                         bitIndex{ -1 };                                     // 20
			stl::enumeration<BindingType, int8_t>          bindingType{ BindingType::BINDING_TYPE_VARIABLE };  // 21
			uint8_t                                        memberType{ 0 };                                    // 22
			int8_t                                         variableType{ -1 };                                 // 23
			stl::enumeration<InternalBindingFlags, int8_t> flags{};                                            // 24
			char                                           pad25[3];                                           // 25
		};
		static_assert(sizeof(Binding) == 0x28);

		inline static constexpr auto RTTI = RTTI_hkbVariableBindingSet;

		hkbVariableBindingSet() { stl::emplace_vtable(this); }
		~hkbVariableBindingSet() override = default;  // 00

		// Properties
		hkArray<Binding> bindings;                // 10
		int32_t          indexOfBindingToEnable;  // 20
		bool             hasOutputBinding;        // 24
	};
	static_assert(sizeof(hkbVariableBindingSet) == 0x28);
}
