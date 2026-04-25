#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkRefPtr.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkbBindableCollector.h"
#include "RE/H/hkbVariableBindingSet.h"

namespace RE
{
	class hkbBindable : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbBindable;
		inline static constexpr auto VTABLE = VTABLE_hkbBindable;

		struct Cache
		{
			// members
			hkbBindable* bindable;                // 00
			uint32_t     indexOfBindingToEnable;  // 08
			bool         hasOutputBinding;        // 0C
			char         pad0D[3];                // 0D
		};
		static_assert(sizeof(Cache) == 0x10);

		hkbBindable() { stl::emplace_vtable(this); }
		~hkbBindable() override = default;  // 00

		HK_HEAP_REDEFINE_NEW();

		// add
		virtual void CollectBindables(hkbBindableCollector& collector) { collector.collectBindable(this); };  // 03

		// members
		hkRefPtr<hkbVariableBindingSet> variableBindingSet;           // 10
		hkArray<hkbBindable*>           cachedBindables;              // 18
		bool                            areBindablesCached{ false };  // 28
		char                            pad29[7];                     // 29
	};
	static_assert(sizeof(hkbBindable) == 0x30);
}
