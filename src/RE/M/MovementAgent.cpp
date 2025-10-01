#include "RE/M/MovementAgent.h"

namespace RE
{
	MovementAgent::MovementAgent()
	{
		stl::emplace_vtable(this);
		managedMovementState = &NullMovementState::QInstance();
	}
}
