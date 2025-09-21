#pragma once

#include "RE/B/BSFixedString.h"

namespace RE
{
	namespace Movement
	{
		struct SPEED_DIRECTIONS
		{
			enum SPEED_DIRECTION : std::uint32_t
			{
				kLeft,
				kRight,
				kForward,
				kBack,
				kRotations,

				kTotal
			};
		};
		using SPEED_DIRECTION = SPEED_DIRECTIONS::SPEED_DIRECTION;

		struct MaxSpeeds
		{
		public:
			enum
			{
				kWalk,
				kRun,

				kTotal
			};

			// members
			float speeds[SPEED_DIRECTIONS::kTotal][kTotal];  // 00
			float rotateWhileMovingRun;                      // 28
		};
		static_assert(sizeof(MaxSpeeds) == 0x2C);

		struct CurrentSpeeds
		{
			// members
			float directional;    // 00
			float movementSpeed;  // 04
			float rotationSpeed;  // 08
		};
		static_assert(sizeof(CurrentSpeeds) == 0x0C);

		struct TypeData
		{
		public:
			// members
			BSFixedString typeName;     // 00 - MNAM
			MaxSpeeds     defaultData;  // 08 - SPED
			CurrentSpeeds currentData;  // 34 - INAM
		};
		static_assert(sizeof(TypeData) == 0x40);
	}
}
