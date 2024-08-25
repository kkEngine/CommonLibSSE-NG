#pragma once

#include "RE/H/hkVector4.h"

namespace RE
{
	class hkMatrix4
	{
	public:
		hkVector4 col0;  // 00
		hkVector4 col1;  // 10
		hkVector4 col2;  // 20
		hkVector4 col3;  // 30
	};
	static_assert(sizeof(hkMatrix4) == 0x40);
}
