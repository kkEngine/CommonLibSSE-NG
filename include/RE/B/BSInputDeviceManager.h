#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTSingleton.h"
#include "RE/I/InputDevices.h"

namespace RE
{
	class BSIInputDevice;
	class BSInputDevice;
	class BSPCGamepadDeviceDelegate;
	class BSPCGamepadDeviceHandler;
	class BSTrackedControllerDevice;
	class BSWin32KeyboardDevice;
	class BSWin32MouseDevice;
	class BSWin32VirtualKeyboardDevice;
	class InputEvent;
	struct BSRemoteGamepadEvent;

	class BSInputDeviceManager :
		public BSTEventSource<InputEvent*>,           // 00
		public BSTSingletonSDM<BSInputDeviceManager>  // 58
	{
	public:
		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                         \
	bool                                 queuedGamepadEnableValue{ false }; /* 00 */ \
	bool                                 valueQueued{ false };              /* 01 */ \
	bool                                 pollingEnabled{ false };           /* 02 */ \
	std::uint8_t                         pad03;                             /* 03 */ \
	std::uint32_t                        pad04;                             /* 04 */ \
	BSTEventSource<BSRemoteGamepadEvent> remoteGamepadEventSource;          /* 08 */ \
	std::uint8_t                         unk60;                             /* 60 */ \
	std::uint8_t                         unk61;                             /* 61 */ \
	std::uint16_t                        unk62;                             /* 62 */ \
	std::uint32_t                        unk64;                             /* 64 */ \
	std::uint64_t                        unk68;                             /* 68 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x70);

		static BSInputDeviceManager* GetSingleton();

		BSPCGamepadDeviceDelegate*    GetGamepad();
		BSPCGamepadDeviceHandler*     GetGamepadHandler();
		BSWin32KeyboardDevice*        GetKeyboard();
		BSWin32MouseDevice*           GetMouse();
		BSTrackedControllerDevice*    GetVRControllerRight();
		BSTrackedControllerDevice*    GetVRControllerLeft();
		BSWin32VirtualKeyboardDevice* GetVirtualKeyboard();
		[[nodiscard]] bool            IsGamepadConnected();
		[[nodiscard]] bool            IsGamepadEnabled();
		[[nodiscard]] bool            IsMouseBackground();
		bool                          GetDeviceKeyMapping(INPUT_DEVICE a_device, std::uint32_t a_key, BSFixedString& a_mapping);
		bool                          GetDeviceMappedKeycode(INPUT_DEVICE a_device, std::uint32_t a_key, std::uint32_t& a_outKeyCode);
		void                          ProcessGamepadEnabledChange();
		void                          ReinitializeMouse();
		void                          CreateInputDevices();
		void                          ResetInputDevices();
		void                          DestroyInputDevices();
		void                          PollInputDevices(float a_secsSinceLastFrame);

		// AE 1.7.99 grew devices[] by two (unused on PC), moving the runtime data from 0x80 to 0x90
		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, REL::Module::IsAtLeast(SKSE::RUNTIME_SSE_1_7_99) ? 0x90 : 0x80, 0x98);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return const_cast<BSInputDeviceManager*>(this)->GetRuntimeData();
		}

		// members
		std::uint8_t    pad59;       // 59
		std::uint16_t   pad5A;       // 5A
		std::uint32_t   pad5C;       // 5C
#ifdef SKYRIM_AE_1799
		BSIInputDevice* devices[INPUT_DEVICE::kTotal];  // 60 - 6 on AE 1.7.99+: [3] and [4] are null on PC, [5] is the virtual keyboard
#else
		BSIInputDevice* devices[4];  // 60
#endif
#ifndef SKYRIM_CROSS_VR
#	if !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
		BSTrackedControllerDevice* unkDevice;     // 80
		BSTrackedControllerDevice* vrDevices[2];  // 88
		RUNTIME_DATA_CONTENT                      // 98
#	elif !defined(ENABLE_SKYRIM_VR)
		RUNTIME_DATA_CONTENT  // 80, 90 on AE 1.7.99+
#	endif
#endif
	};
#if defined(SKYRIM_AE_1799)
	static_assert(sizeof(BSInputDeviceManager) == 0x100);
#elif !defined(ENABLE_SKYRIM_VR)
	static_assert(sizeof(BSInputDeviceManager) == 0xF0);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(BSInputDeviceManager) == 0x108);
#else
	static_assert(sizeof(BSInputDeviceManager) == 0x80);
#endif
}
#undef RUNTIME_DATA_CONTENT
