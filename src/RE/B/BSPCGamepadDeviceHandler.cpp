#include "RE/B/BSPCGamepadDeviceHandler.h"

namespace RE
{
	void BSPCGamepadDeviceHandler::InitializeDelegate()
	{
		using func_t = decltype(&BSPCGamepadDeviceHandler::InitializeDelegate);
		REL::Relocation<func_t> func{ REL::ID(68762) };
		return func(this);
	}

	BSPCGamepadDeviceHandler::BSPCGamepadDeviceHandler() :
		BSIInputDevice(),
		currentPCGamePadDelegate(nullptr)
	{}
}
