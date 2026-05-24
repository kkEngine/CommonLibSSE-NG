#include "RE/H/hkpEntityListener.h"

namespace RE
{
	void hkpEntityListener::EntityShapeSetCallback(hkpEntity* a_entity)
	{
		REL::RelocateVirtual<decltype(&hkpEntityListener::EntityShapeSetCallback)>(0x3, 0, this, a_entity);
	}
}
