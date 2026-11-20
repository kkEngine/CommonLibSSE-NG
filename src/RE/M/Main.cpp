#include "RE/M/Main.h"

#include "RE/N/NiCamera.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	Main* Main::GetSingleton()
	{
		REL::Relocation<Main**> singleton{ Offset::Main::Singleton };
		return *singleton;
	}

	float Main::QFrameAnimTime()
	{
		REL::Relocation<float*> data{ REL::ID(403447) };
		return *data;
	}

	NiCamera* Main::WorldRootCamera()
	{
		using func_t = decltype(&Main::WorldRootCamera);
		REL::Relocation<func_t> func{ REL::ID(36609) };
		return func();
	}

	Scenegraph* Main::WorldRootNode()
	{
		REL::Relocation<NiPointer<Scenegraph>*> nodePtr{ REL::ID(403513) };
		return nodePtr->get();
	}

	void Main::SetActive(bool a_active)
	{
		using func_t = decltype(&Main::SetActive);
		REL::Relocation<func_t> func{ REL::ID(36606) };
		return func(this, a_active);
	}
}
