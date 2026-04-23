#pragma once

namespace RE
{
	class hkbBindable;

	class hkbBindableCollector
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbBindableCollector;

		// Called on each hkbBindable when you pass this collector into hkbBindable::collectBindables().
		virtual void collectBindable(hkbBindable* bindable) = 0;  // 00
		virtual ~hkbBindableCollector() = default;                // 01
	};
	static_assert(sizeof(hkbBindableCollector) == 0x8);
}
