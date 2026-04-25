#pragma once

#include "RE/H/hkBaseObject.h"
#include "RE/H/hkMemoryAllocator.h"
#include "RE/H/hkMemoryRouter.h"

namespace RE
{
	class hkClass;
	class hkStatisticsCollector;

	class hkReferencedObject : public hkBaseObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkReferencedObject;
		inline static constexpr auto VTABLE = VTABLE_hkReferencedObject;

		enum class LockMode
		{
			kNone = 0,
			kAuto,
			kManual
		};

		enum
		{
			kMemSize = 0x7FFF
		};

		hkReferencedObject() { stl::emplace_vtable(this); }
		~hkReferencedObject() override = default;  // 00

		HK_HEAP_REDEFINE_NEW();

		// add
		virtual const hkClass* GetClassType() const;                                                                     // 01 - { return 0; }
		virtual void           CalcContentStatistics(hkStatisticsCollector* a_collector, const hkClass* a_class) const;  // 02

		void         AddReference() const;
		std::int32_t GetAllocatedSize() const;
		std::int32_t GetReferenceCount() const;
		void         RemoveReference() const;

		// members
		std::uint16_t                 memSizeAndFlags{ 0xffff };  // 08
		volatile mutable std::int16_t referenceCount{ 1 };        // 0A
		std::uint32_t                 pad0C;                      // 0C
	};
	static_assert(sizeof(hkReferencedObject) == 0x10);
}
