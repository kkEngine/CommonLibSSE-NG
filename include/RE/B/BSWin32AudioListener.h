#pragma once

#include "RE/B/BSAudioListener.h"
#include "REX/W32/DSOUND.h"

namespace RE
{
	// Adapted from Fallout3 RE. May contain errors.
	class BSWin32AudioListener : public BSAudioListener
	{
	public:
		BSWin32AudioListener();
		~BSWin32AudioListener() override;  // 00

		// members
		REX::W32::IDirectSound3DListener* listener;          // 50
		NiPoint3                          topOrientation;    // 58
		NiPoint3                          frontOrientation;  // 64
	};
	static_assert(sizeof(BSWin32AudioListener) == 0x70);
}
