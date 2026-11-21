#include "RE/N/NullMovementState.h"

namespace RE
{
	NullMovementState& NullMovementState::QInstance()
	{
		if (REL::Module::IsSE()) {
			using func_t = decltype(&NullMovementState::QInstance);
			REL::Relocation<func_t> func{ RELOCATION_ID(89473, 0) };
			return func();
		} else if (REL::Module::IsAE()) {
			// In version 1.6.1170 there is no separate "QInstance" function, it is inlined
			// Because of this, u can get a nullptr (uninitialized singleton) if no one has initialized it before
			REL::Relocation<std::uintptr_t> NullMovementState_Instance{ RELOCATION_ID(525786, 412263) };
			return *reinterpret_cast<NullMovementState*>(NullMovementState_Instance.address());
		}

		throw std::runtime_error("Can't execute NullMovementState::QInstance() because there is no implementation");
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
		REL::Relocation<func_t> func{ RELOCATION_ID(88523, 90949) };
		return func(this);
	}
}
