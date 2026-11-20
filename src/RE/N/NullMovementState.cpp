#include "RE/N/NullMovementState.h"

namespace RE
{
	NullMovementState& NullMovementState::QInstance()
	{
		// There is no separate "QInstance" function, it is inlined: the object is uninitialized until someone initializes it
		REL::Relocation<std::uintptr_t> instance{ REL::ID(412263) };
		return *reinterpret_cast<NullMovementState*>(instance.address());
	}

	void NullMovementState::DoGetLocation(NiPoint3& pos) const
	{
		pos = RE::NiPoint3();
	}

	void NullMovementState::DoGetEulerAngles(NiPoint3& angles) const
	{
		angles = RE::NiPoint3();
	}

	IMovementParameters* NullMovementState::DoGetDefaultMovementParameters() const
	{
		using func_t = decltype(&NullMovementState::DoGetDefaultMovementParameters);
		REL::Relocation<func_t> func{ REL::ID(90949) };
		return func(this);
	}
}
