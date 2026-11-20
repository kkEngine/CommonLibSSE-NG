#include "RE/O/ObjectiveState.h"

namespace RE
{
	BSTEventSource<ObjectiveState::Event>* ObjectiveState::GetEventSource()
	{
		using func_t = decltype(&ObjectiveState::GetEventSource);
		REL::Relocation<func_t> func{ REL::ID(23951) };
		return func();
	}
}
