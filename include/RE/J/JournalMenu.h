#pragma once

#include "RE/B/BSTEvent.h"
#include "RE/I/IMenu.h"
#include "RE/J/Journal_QuestsTab.h"
#include "RE/J/Journal_StatsTab.h"
#include "RE/J/Journal_SystemTab.h"
#include "RE/M/MenuEventHandler.h"

namespace RE
{
	class BSSystemEvent;

	// menuDepth = 5
	// flags = kPausesGame | kUsesMenuContext | kFreezeFrameBackground | kRequiresUpdate | kTopmostRenderedMenu | kUpdateUsesCursor | kAllowSaving
	// kDisablePauseMenu if game load prevented
	// context = kJournal
	class JournalMenu :
		public IMenu,  // 00
		public MenuEventHandler,            // 30
		public BSTEventSink<BSSystemEvent>  // 40
	{
	public:
		inline static constexpr auto      RTTI = RTTI_JournalMenu;
		inline static constexpr auto      VTABLE = VTABLE_JournalMenu;
		constexpr static std::string_view MENU_NAME = "Journal Menu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT              \
	Journal_QuestsTab questsTab; /* 00 */ \
	Journal_StatsTab  statsTab;  /* 38 */ \
	Journal_SystemTab systemTab; /* 50 */ \
	std::uint64_t     unkD0;     /* 88 */ \
	std::uint64_t     unkD8;     /* 90 */ \
	std::uint64_t     unkE0;     /* 98 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0xA0);

		~JournalMenu() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;                       // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;                         // 04
		void               AdvanceMovie(float a_interval, std::uint32_t a_currentTime) override;  // 05
		void               PostDisplay() override;                                                // 06

		// override (MenuEventHandler)
		bool CanProcess(InputEvent* a_event) override;              // 01
		bool ProcessThumbstick(ThumbstickEvent* a_event) override;  // 03

		// override (BSTEventSink<BSSystemEvent>)
		BSEventNotifyControl ProcessEvent(const BSSystemEvent* a_event, BSTEventSource<BSSystemEvent>* a_eventSource) override;  // 01

		[[nodiscard]] MenuEventHandler* AsMenuEventHandler() noexcept
		{
			return &REL::RelocateMember<MenuEventHandler>(this, 0x30);
		}

		[[nodiscard]] const MenuEventHandler* AsMenuEventHandler() const noexcept
		{
			return const_cast<JournalMenu*>(this)->AsMenuEventHandler();
		}

		[[nodiscard]] BSTEventSink<BSSystemEvent>* AsBSSystemEventSink() noexcept
		{
			return &REL::RelocateMember<BSTEventSink<BSSystemEvent>>(this, 0x40);
		}

		[[nodiscard]] const BSTEventSink<BSSystemEvent>* AsBSSystemEventSink() const noexcept
		{
			return const_cast<JournalMenu*>(this)->AsBSSystemEventSink();
		}

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x48);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x48);
		}

		// members
		RUNTIME_DATA_CONTENT  // 48, 58
	};
	static_assert(sizeof(JournalMenu) == 0xE8);
}
#undef RUNTIME_DATA_CONTENT
