#pragma once

namespace RE
{
	struct INPUT_DEVICES
	{
		enum INPUT_DEVICE
		{
			kNone = static_cast<std::underlying_type_t<INPUT_DEVICE>>(-1),
			kKeyboard = 0,
			kMouse,
			kGamepad,
#ifdef SKYRIM_AE_1799
			// AE 1.7.99 inserted two devices before the virtual keyboard (the game's device factory
			// switch and the 6 mapping arrays of every ControlMap context). They are not created on PC;
			// the NX controlmap.txt names their columns "Gesture ID" and "Gamepad button except Look
			// is mapped to Mouse".
			kGesture = 3,
			kUnknown4 = 4,
			kVirtualKeyboard = 5,
#else
			kVirtualKeyboard,
#endif

			kTotal
		};
		static_assert(sizeof(INPUT_DEVICE) == 0x4);
	};
	using INPUT_DEVICE = INPUT_DEVICES::INPUT_DEVICE;
}
