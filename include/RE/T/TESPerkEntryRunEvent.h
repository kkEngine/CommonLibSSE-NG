#pragma once

#include "RE/N/NiSmartPointer.h"
#include "RE/T/TESObjectREFR.h"

namespace RE
{
	struct TESPerkEntryRunEvent
	{
		RE::NiPointer<RE::TESObjectREFR> target;         // 00
		RE::NiPointer<RE::TESObjectREFR> owner;          // 08
		RE::FormID                       perkFormId;     // 10
		std::uint16_t                    fragmentIndex;  // 14 - perk script fragment index
		std::uint16_t                    pad16;          // 16
	};
	static_assert(sizeof(TESPerkEntryRunEvent) == 0x18);
}
