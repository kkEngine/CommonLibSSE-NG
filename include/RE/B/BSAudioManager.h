#pragma once

#include "RE/B/BSAudioManagerThread.h"
#include "RE/B/BSFixedString.h"
#include "RE/B/BSTHashMap.h"
#include "RE/N/NiTPointerList.h"

namespace RE
{
	class BSISoundDescriptor;
	class BSXAudio2GameSound;
	class BSSoundMessage;
	struct BSSoundHandle;

	namespace BSResource
	{
		struct ID;
	}

	class BSAudioManager
	{
	public:
		class SoundMessageStack
		{
		public:
			uint32_t        count;
			bool            bottomless;
			BSSoundMessage* top;
			uint32_t        timeLastAllocated;

			void            Push(BSSoundMessage* apMessage);
			BSSoundMessage* Pop();
		};
		static_assert(sizeof(SoundMessageStack) == 0x18);

		static BSAudioManager* GetSingleton();

		bool Play(FormID a_soundFormID);
		bool Play(BSISoundDescriptor* a_descriptor);
		bool BuildSoundDataFromDescriptor(BSSoundHandle& a_soundHandle, BSISoundDescriptor* a_descriptor, std::uint32_t a_flags = 0x1A);
		void BuildSoundDataFromEditorID(BSSoundHandle& a_soundHandle, const char* a_editorID, std::uint32_t a_flags);
		void BuildSoundDataFromFile(BSSoundHandle& a_soundHandle, const BSResource::ID& a_file, std::uint32_t a_flags, std::uint32_t a_priority);

		// members
		uint32_t                                       messageListIndex;            // 000
		uint32_t                                       messageProcessingListIndex;  // 004
		NiTPointerList<BSSoundMessage*>*               messages[2];                 // 008
		SoundMessageStack*                             freeMessages;                // 018
		SoundMessageStack*                             garbageMessages;             // 020
		std::uint64_t                                  unk028;                      // 028 - mb SoundMessageStack*
		BSTHashMap<std::uint32_t, BSXAudio2GameSound*> unk030;                      // 030
		BSTHashMap<UnkKey, UnkValue>                   unk060;                      // 060
		BSTHashMap<UnkKey, UnkValue>                   unk090;                      // 090
		BSTHashMap<UnkKey, UnkValue>                   unk0C0;                      // 0C0
		std::uint64_t                                  unk0F0;                      // 0F0
		BSAudioManagerThread*                          unk0F8;                      // 0F8
		std::uint64_t                                  unk100;                      // 100
		BSFixedString                                  unk108;                      // 108
		std::uint64_t                                  unk110;                      // 110
		std::uint64_t                                  unk118;                      // 118
		std::uint64_t                                  unk120;                      // 120
		std::uint64_t                                  unk128;                      // 128
		std::uint64_t                                  unk130;                      // 130
		std::uint64_t                                  unk138;                      // 138
		std::uint64_t                                  unk140;                      // 140
		std::uint64_t                                  unk148;                      // 148
		std::uint64_t                                  unk150;                      // 150
		std::uint64_t                                  unk158;                      // 158
		std::uint64_t                                  unk160;                      // 160
		std::uint64_t                                  unk168;                      // 168
		std::uint64_t                                  unk170;                      // 170
		std::uint64_t                                  unk178;                      // 178
		std::uint64_t                                  unk180;                      // 180
		std::uint64_t                                  unk188;                      // 188
	};
	static_assert(sizeof(BSAudioManager) == 0x190);
}
