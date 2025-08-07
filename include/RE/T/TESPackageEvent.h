#pragma once

namespace RE
{
	struct TESPackageEvent
	{
		enum class EventType : std::uint32_t
		{
			kStart = 0,
			kChange = 1,
			kEnd = 2
		};

		RE::TESObjectREFR* actor;
		RE::FormID         package;
		EventType          type;
	};
}
