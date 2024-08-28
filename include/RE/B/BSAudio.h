#pragma once

namespace RE
{
	class TESSound;
	class BSWin32GameSound;
	class BSWin32AudioListener;

	// Adapted from Fallout3 RE. May contain errors.
	class BSAudio
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSAudio;

		struct AudioTick
		{
			uint32_t unk0;      // 0
			uint32_t lastTick;  // 4
			uint32_t flags;     // 8
		};
		static_assert(sizeof(AudioTick) == 0xC);

		BSAudio();
		virtual ~BSAudio();  // 00

		// add
		virtual void              Init(HWND* a_apWindow) = 0;                    // 01
		virtual void              Shutdown() = 0;                                // 02
		virtual void              Unk_03(int) = 0;                               // 03
		virtual uint32_t          Unk_04() = 0;                                  // 04
		virtual BSWin32GameSound* GetGameSound(const char* a_apPath) = 0;        // 05
		virtual void              PrependDataSoundPath(char* a_apFilename) = 0;  // 06 - Prefixes path with data\\sound\\ if fx\\ or song\\.
		virtual void              Unk_07() = 0;                                  // 07

		// members
		bool                  ready;                                                                                                   // 08
		bool                  isInitialized;                                                                                           // 09
		bool                  isMultithreaded;                                                                                         // 0A
		uint8_t               pad0B;                                                                                                   // 0B
		uint32_t              unk0C;                                                                                                   // 0C
		uint8_t               unk10;                                                                                                   // 10
		uint8_t               pad11;                                                                                                   // 11
		uint16_t              pad12;                                                                                                   // 12
		uint32_t              pad14;                                                                                                   // 14
		BSWin32AudioListener* listener;                                                                                                // 18
		AudioTick             timePassed;                                                                                              // 20
		uint32_t              pad2C;                                                                                                   // 2C
		bool(__cdecl* GetSoundDataFromRefID)(uint32_t a_refID, char* a_outFilePath, uint32_t* a_outFlags, TESSound** a_outSound);      // 30
		bool(__cdecl* GetSoundDataFromEDID)(const char* a_EDIDstr, char* a_outFilePath, uint32_t* a_outFlags, TESSound** a_outSound);  // 38
		bool(__cdecl* PickSoundFileFromFolder)(char* a_outFilePath);                                                                   // 40
		uint32_t(__cdecl* FillGameSoundProps)(uint32_t* a_mapKey, TESSound* a_soundForm, uint32_t* a_outFlags0C);                      // 48
		void (*unk50)(void);                                                                                                           // 50
		void (*unk58)(void);                                                                                                           // 58
	};
	static_assert(sizeof(BSAudio) == 0x60);
}
