#pragma once

#include "REX/W32/COM.h"

namespace REX::W32
{
	struct DSBCAPS
	{
		std::uint32_t dwSize;
		std::uint32_t dwFlags;
		std::uint32_t dwBufferBytes;
		std::uint32_t dwUnlockTransferRate;
		std::uint32_t dwPlayCpuOverhead;
	};
}

namespace REX::W32
{
	// See #include <dsound.h>
	struct IDirectSound8;
	struct IDirectSoundBuffer8;
	struct IDirectSound3DListener;
}

