#pragma once

#include "RE/B/BSTEvent.h"
#include "RE/I/IMenu.h"

namespace RE
{
	class HudModeChangeEvent;

	// menuDepth = 4
	// context = 22
	class WorldSpaceMenu :
		public IMenu,                            // 00
		public BSTEventSink<HudModeChangeEvent>  // 40
	{
	public:

		~WorldSpaceMenu() override;  // 00

		[[nodiscard]] BSTEventSink<HudModeChangeEvent>* AsHudModeChangeEventSink() noexcept
		{
			if (!REL::Module::IsVR()) {
				return nullptr;
			}
			return &REL::RelocateMember<BSTEventSink<HudModeChangeEvent>>(this, 0, 0x40);
		}

		[[nodiscard]] const BSTEventSink<HudModeChangeEvent>* AsHudModeChangeEventSink() const noexcept
		{
			return const_cast<WorldSpaceMenu*>(this)->AsHudModeChangeEventSink();
		}

	};
}
