#pragma once

namespace RE
{
	class hkbGeneratorSyncInfo
	{
	public:
		/// The description of a point on the timeline that is used for synchronization.
		struct SyncPoint
		{
			// This must be trivial, as it is called from the finish constructor
			SyncPoint() = default;

			// Actually init the SyncPoint
			void init()
			{
				externalEventId = INVALID_ID;
				time = 0.0f;
			}

			enum
			{
				INVALID_ID = -1,
				START_OF_GENERATOR_ID = -2
			};

			// members
			int32_t externalEventId;  // 00 - The id of the sync point.
			float   time;             // 04 - The point on the timeline where this sync point is.
		};

		/// Copy constructor copies everything but then clears the m_isMirrored flag.
		hkbGeneratorSyncInfo(const hkbGeneratorSyncInfo& syncInfo)
		{
			std::memcpy(this, &syncInfo, sizeof(hkbGeneratorSyncInfo));
			isMirrored = false;
		}

		/// Assignment copies everything but then clears the m_isMirrored flag.
		hkbGeneratorSyncInfo& operator=(const hkbGeneratorSyncInfo& syncInfo)
		{
			std::memcpy(this, &syncInfo, sizeof(hkbGeneratorSyncInfo));
			isMirrored = false;
			return *this;
		}

		// members
		SyncPoint syncPoints[8];  // 00
		float     duration;       // 40 - baseFrequency
		float     localTime;      // 44
		float     playbackSpeed;  // 48
		uint8_t   numSyncPoints;  // 4C
		bool      isCyclic;       // 4D
		bool      isMirrored;     // 4E
		bool      isAdditive;     // 4F
	};
	static_assert(sizeof(hkbGeneratorSyncInfo) == 0x50);
}
