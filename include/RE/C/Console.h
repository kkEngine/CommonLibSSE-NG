#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/I/IMenu.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class TESObjectREFR;

	// menuDepth = 12
	// flags = kPausesGame | kAlwaysOpen | kUsesCursor | kAllowSaving
	// context = kConsole
	class Console : public IMenu
	{
	public:
		inline static constexpr auto      RTTI = RTTI_Console;
		constexpr static std::string_view MENU_NAME = "Console";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT       \
	void*         opcode; /* 00 */ \
	std::uint64_t unk38;  /* 08 */ \
	std::uint64_t unk40;  /* 10 */

			RUNTIME_DATA_CONTENT
		};

		struct RUNTIME_DATA2
		{
#define RUNTIME_DATA_CONTENT2                      \
	std::uint64_t unk48;                  /* 18 */ \
	std::uint64_t selectedRefHandleIndex; /* 20 */

			RUNTIME_DATA_CONTENT2
		};

		~Console() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;  // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;    // 04

		static NiPointer<TESObjectREFR> GetSelectedRef();
		static ObjectRefHandle          GetSelectedRefHandle();

		void SelectReference();
		void SetSelectedRef(NiPointer<TESObjectREFR> a_refPtr);
		void SetSelectedRef(TESObjectREFR* a_ref);
		void SetSelectedRef(ObjectRefHandle a_handle);

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x30);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x30);
		}

		[[nodiscard]] inline RUNTIME_DATA2& GetRuntimeData2() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA2>(this, 0x48);
		}

		[[nodiscard]] inline const RUNTIME_DATA2& GetRuntimeData2() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA2>(this, 0x48);
		}

		// members
		RUNTIME_DATA_CONTENT
		RUNTIME_DATA_CONTENT2

	protected:
		void
			SetSelectedRef_Impl(ObjectRefHandle& a_handle);
	};
}
#undef RUNTIME_DATA_CONTENT
#undef RUNTIME_DATA_CONTENT2
