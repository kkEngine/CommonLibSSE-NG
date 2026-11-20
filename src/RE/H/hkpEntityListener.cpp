#include "RE/H/hkpEntityListener.h"

namespace RE
{
	void hkpEntityListener::EntityShapeSetCallback(hkpEntity* a_entity)
	{
		using func_t = void(hkpEntityListener*, hkpEntity*);
		(*reinterpret_cast<func_t***>(this))[0x3](this, a_entity);
	}
}
