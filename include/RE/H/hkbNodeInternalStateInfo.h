#pragma once

#include "RE/H/hkRefPtr.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkStringPtr.h"
#include "RE/H/hkbGeneratorSyncInfo.h"

namespace RE
{
	class hkbNodeInternalStateInfo : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbNodeInternalStateInfo;

		~hkbNodeInternalStateInfo() override;  // 00

		hkbGeneratorSyncInfo         syncInfo;               // 10
		hkStringPtr                  name;                   // 60
		hkRefPtr<hkReferencedObject> internalState;          // 68
		int16_t                      nodeId;                 // 70
		bool                         hasActivateBeenCalled;  // 72
	};
	static_assert(sizeof(hkbNodeInternalStateInfo) == 0x78);
}
