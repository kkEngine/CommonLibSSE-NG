#pragma once

#include "RE/N/NiSmartPointer.h"
#include "RE/T/TESObjectREFR.h"

namespace RE
{
	struct TESObjectREFRTranslationEvent
	{
		enum class EventType : std::uint32_t
		{
			kFailed = 0,
			kCompleted = 1,
			kAlmostCompleted = 2
		};

		RE::NiPointer<RE::TESObjectREFR> refr;   // 00
		EventType                        type;   // 08
		std::uint32_t                    pad0C;  // 0C
	};
	static_assert(sizeof(TESObjectREFRTranslationEvent) == 0x10);
}
