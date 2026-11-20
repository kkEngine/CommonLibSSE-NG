#pragma once

#include "RE/B/BSSoundHandle.h"
#include "RE/B/BSTEvent.h"
#include "RE/I/IMenu.h"
#include "RE/M/MenuEventHandler.h"
#include "RE/N/NiMatrix3.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class MenuOpenCloseEvent;
	class NiAVObject;
	class NiControllerManager;
	class NiControllerSequence;
	class TESObjectREFR;

	// menuDepth = 3
	// flags = kPausesGame | kDisablePauseMenu | kRequiresUpdate
	// context = kLockpicking
	class LockpickingMenu :
		public IMenu,  // 00
		public MenuEventHandler,                 // 30
		public BSTEventSink<MenuOpenCloseEvent>  // 40
	{
	public:
		inline static constexpr auto      RTTI = RTTI_LockpickingMenu;
		inline static constexpr auto      VTABLE = VTABLE_LockpickingMenu;
		constexpr static std::string_view MENU_NAME = "Lockpicking Menu";

		// AE 1.7.99 inserted 0x14 bytes after pickBreakSeconds (seen in the ctor)
#	define LOCKPICKING_AE1799_CONTENT \
		std::uint32_t unkA4;           \
		std::uint32_t unkA8;           \
		std::uint16_t unkAC;           \
		std::uint8_t  unkAE;           \
		std::uint8_t  padAF;           \
		std::uint64_t unkB0;

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                            \
	void*                 lockpickShiv;        /* 00 */ \
	void*                 lockpick;            /* 08 */ \
	NiMatrix3             pickRotation;        /* 10 */ \
	NiPoint3              lockRotCenter;       /* 34 */ \
	NiControllerManager*  lockController;      /* 40 */ \
	NiControllerSequence* lockIntro;           /* 48 */ \
	NiControllerSequence* lockRotate;          /* 50 */ \
	NiControllerManager*  pickController;      /* 58 */ \
	NiControllerSequence* pickIntro;           /* 60 */ \
	NiControllerSequence* pickDamage;          /* 68 */ \
	NiControllerSequence* pickBreak;           /* 70 */ \
	NiControllerSequence* currentPickSequence; /* 78 */ \
	float                 pickKeyTime;         /* 80 */ \
	std::uint32_t         unk0CC;              /* 84 */ \
	NiControllerSequence* currentLockSequence; /* 88 */ \
	float                 lockKeyTime;         /* 90 */ \
	float                 pickAngle;           /* 94 */ \
	float                 lockAngle;           /* 98 */ \
	float                 damagePickAngle;     /* 9C */ \
	float                 pickBreakSeconds;    /* A0 */ \
	LOCKPICKING_AE1799_CONTENT                 /* A4 */ \
	BSSoundHandle         pickTensionSound;    /* A4, B8 on AE 1.7.99+ (all below + 0x14) */ \
	float                 unk0F8;              /* B0 */ \
	float                 sweetSpotAngle;      /* B4 */ \
	float                 partialPickAngle;    /* B8 */ \
	std::uint32_t         numBrokenPicks;      /* BC */ \
	bool                  init3DElements;      /* C0 */ \
    bool                  animating;           /* C1 */ \
	bool                  unk10A;              /* C2 */ \
	bool                  menuCleared;         /* C3 */ \
	bool                  animationFinished;   /* C4 */ \
	bool                  isLockpickingCrime;  /* C5 */ \
	std::uint8_t          unk10E;              /* C6 */ \
	std::uint8_t          pad10F;              /* C7 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0xE0);

		~LockpickingMenu() override;  // 00

		// override (IMenu)
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;  // 04

		// override (MenuEventHandler)
		bool CanProcess(InputEvent* a_event) override;              // 01
		bool ProcessThumbstick(ThumbstickEvent* a_event) override;  // 03
		bool ProcessMouseMove(MouseMoveEvent* a_event) override;    // 04
		bool ProcessButton(ButtonEvent* a_event) override;          // 05

		// override (BSTEventSink<MenuOpenCloseEvent>)
		BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent* a_event, BSTEventSource<MenuOpenCloseEvent>* a_eventSource) override;  // 01

		[[nodiscard]] static TESObjectREFR* GetTargetReference();

		[[nodiscard]] MenuEventHandler* AsMenuEventHandler() noexcept
		{
			return &REL::RelocateMember<MenuEventHandler>(this, 0x30);
		}

		[[nodiscard]] const MenuEventHandler* AsMenuEventHandler() const noexcept
		{
			return const_cast<LockpickingMenu*>(this)->AsMenuEventHandler();
		}

		[[nodiscard]] BSTEventSink<MenuOpenCloseEvent>* AsMenuOpenCloseEventSink() noexcept
		{
			return &REL::RelocateMember<BSTEventSink<MenuOpenCloseEvent>>(this, 0x40);
		}

		[[nodiscard]] const BSTEventSink<MenuOpenCloseEvent>* AsMenuOpenCloseEventSink() const noexcept
		{
			return const_cast<LockpickingMenu*>(this)->AsMenuOpenCloseEventSink();
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
	static_assert(sizeof(LockpickingMenu) == 0x128);
}
#undef RUNTIME_DATA_CONTENT
#undef LOCKPICKING_AE1799_CONTENT
