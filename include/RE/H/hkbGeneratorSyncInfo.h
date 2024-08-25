#pragma once

namespace RE
{
	class hkbGeneratorSyncInfo
	{
	public:
		struct SyncPoint
		{
			int   id;    // 00
			float time;  // 04
		};
		static_assert(sizeof(SyncPoint) == 0x08);

		SyncPoint syncPoints[8];  // 00
		float     baseFrequency;  // 40
		float     localTime;      // 44
		float     playbackSpeed;  // 48
		int8_t    numSyncPoints;  // 4C
		bool      isCyclic;       // 4D
		bool      isMirrored;     // 4E
		bool      isAdditive;     // 4F
	};
	static_assert(sizeof(hkbGeneratorSyncInfo) == 0x50);
}
