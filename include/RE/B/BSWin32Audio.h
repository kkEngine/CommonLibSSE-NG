#pragma once

#include "RE/B/BSAudio.h"
#include "REX/W32/DSOUND.h"

namespace RE
{
	// Adapted from Fallout3 RE. May contain errors.
	class BSWin32Audio : public BSAudio
	{
	public:
		BSWin32Audio();
		~BSWin32Audio() override;

		struct BufferCaps : public REX::W32::DSBCAPS
		{
			uint32_t unk054;
			uint32_t unk058;
			uint32_t unk05C;
			bool     bUseHRTF;
			uint8_t  pad1;
			uint16_t pad2;
			uint32_t unk064;
			uint32_t unk068;
			uint32_t unk06C;
			uint32_t unk070;
			uint32_t unk074;
			uint32_t unk078;
			uint32_t unk07C;
			uint32_t unk080;
			uint32_t unk084;
			uint32_t unk088;
			uint32_t unk08C;
			uint32_t unk090;
			uint32_t unk094;
			uint32_t unk098;
			uint32_t unk09C;
		};
		static_assert(sizeof(BufferCaps) == 0x60);

		static BSWin32Audio* GetSingleton();
		static void __stdcall Create();

		void ControlAudioThread(bool abEnable);

		// members
		REX::W32::IDirectSound8*       directSound8;       // 60
		REX::W32::IDirectSoundBuffer8* directSoundBuffer;  // 68
		BufferCaps                     dsbCaps;            // 70
		REX::W32::HWND                 window;             // D0
	};
	static_assert(sizeof(BSWin32Audio) == 0xD8);
	const auto tt = offsetof(BSWin32Audio, window);
}
