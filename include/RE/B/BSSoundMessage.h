#pragma once

#include "RE/N/NiRefObject.h"

namespace RE
{
	// Adapted from Fallout3 RE. May contain errors.
	class BSSoundMessage
	{
	public:
		uint32_t               type;     // 00
		uint32_t               id;       // 04
		int32_t                data;     // 08
		uint32_t               pad0C;    // 0C
		BSSoundMessage*        next;     // 10
		NiPointer<NiRefObject> objData;  // 18
		union
		{
			float    vector[3];
			uint16_t curve[5];
		};               // 20
		uint32_t pad2C;  // 2C
	};
	static_assert(sizeof(BSSoundMessage) == 0x30);
}
