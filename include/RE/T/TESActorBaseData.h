#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/BaseFormComponent.h"
#include "RE/F/FactionRank.h"

namespace RE
{
	class BGSVoiceType;
	class TESActorBase;
	class TESFaction;
	class TESForm;
	class TESLevItem;
	class TESNPC;

	struct ACTOR_BASE_DATA
	{
	public:
		enum class Flag
		{
			kNone = 0,
			kFemale = 1 << 0,
			/// <summary>
			/// Essential Actors cannot be killed. When they reach 0 health, they go into a special "bleedout" state and recover over time.
			/// </summary>
			kEssential = 1 << 1,
			/// <summary>
			/// If checked, the face created for this actor is available for the player to choose in Character Gen. 
			/// There is a misconception that this flag will also prevent CK from editing the NPC's Face Data, 
			/// and some mods have used this heavily on their NPC's resulting in a heavily populated Character Gen menu. 
			/// Do not use unless you wish this face to be an available Preset for the Player.
			/// </summary>
			kIsChargenFacePreset = 1 << 2,
			/// <summary>
			/// References of this Actor in the world will resurrect and reset when their cell is reset. The Actor will respawn at their original Editor Location.
			/// </summary>
			kRespawn = 1 << 3,
			kAutoCalcStats = 1 << 4,
			/// <summary>
			/// Only one reference of this Actor is allowed to exist. Unique actors mainly exist so that the Story Manager can find them even when they are not currently persisting.
			/// </summary>
			kUnique = 1 << 5,
			/// <summary>
			/// When this Actor detects the Player, the stealth meter does not react. Typically used for non-hostile actors such as animals and critters.
			/// </summary>
			kDoesntAffectStealthMeter = 1 << 6,
			kPCLevelMult = 1 << 7,
			kUsesTemplate = 1 << 8,
			kCalcForAllTemplates = 1 << 9,
			/// <summary>
			/// Protected Actors are treated as essential to all damage except that delivered by the Player. The Player is the only one allowed to kill a Protected Actor.
			/// </summary>
			kProtected = 1 << 11,
			kNoRumors = 1 << 13,
			/// <summary>
			/// This Actor can be associated with a Summon Actor magic effect.
			/// </summary>
			kSummonable = 1 << 14,
			/// <summary>
			/// When the Actor is struck by a weapon, blood effects are disabled.
			/// </summary>
			kDoesntBleed = 1 << 16,
			kBleedoutOverride = 1 << 18,
			kOppositeGenderAnims = 1 << 19,
			/// <summary>
			/// Disables face animations and morphing. Also disables the Story Manager's Death and Assault events.
			/// </summary>
			kSimpleActor = 1 << 20,
			kLoopedScript = 1 << 21,  // ?
			kNoActivation = 1 << 23,
			kLoopedAudio = 1 << 28,  // ?
			/// <summary>
			/// This Actor is immune to all damage, and all weapons pass through them without playing hit effects or triggering hit events.
			/// </summary>
			kIsGhost = 1 << 29,
			/// <summary>
			/// This Actor is immune to all damage, although weapons and projectiles appear to hit them normally.
			/// </summary>
			kInvulnerable = 1 << 31
		};

		enum class TEMPLATE_USE_FLAG
		{
			kNone = 0,
			kTraits = 1 << 0,
			kStats = 1 << 1,
			kFactions = 1 << 2,
			kSpells = 1 << 3,
			kAIData = 1 << 4,
			kAIPackages = 1 << 5,
			kUnused = 1 << 6,
			kBaseData = 1 << 7,
			kInventory = 1 << 8,
			kScript = 1 << 9,
			kAIDefPackList = 1 << 10,
			kAttackData = 1 << 11,
			kKeywords = 1 << 12,
			kCopiedTemplate = 1 << 15
		};

		// members
		stl::enumeration<Flag, std::uint32_t>              actorBaseFlags;    // 00
		std::int16_t                                       magickaOffset;     // 04
		std::int16_t                                       staminaOffset;     // 06
		std::uint16_t                                      level;             // 08
		std::uint16_t                                      calcLevelMin;      // 0A
		std::uint16_t                                      calcLevelMax;      // 0C
		std::uint16_t                                      speedMult;         // 0E
		std::uint16_t                                      baseDisposition;   // 10 - unused
		stl::enumeration<TEMPLATE_USE_FLAG, std::uint16_t> templateUseFlags;  // 12
		std::int16_t                                       healthOffset;      // 14
		std::int16_t                                       bleedoutOverride;  // 16
	};
	static_assert(sizeof(ACTOR_BASE_DATA) == 0x18);

	class TESActorBaseData : public BaseFormComponent  // ACBS
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESActorBaseData;

		~TESActorBaseData() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;                // 01
		void ClearDataComponent() override;                     // 02
		void CopyComponent(BaseFormComponent* a_rhs) override;  // 03

		// add
		virtual void               CopyFromTemplateForms(TESActorBase** a_templateForms);  // 04 - { return; }
		[[nodiscard]] virtual bool GetIsGhost() const;                                     // 05 - { return (flags >> 29) & 1; }
		[[nodiscard]] virtual bool GetInvulnerable() const;                                // 06 - { test flags, 80000000h; }
		virtual void               Unk_07(void);                                           // 07 - { return 1; }
		virtual BGSVoiceType*      GetVoiceType(void);                                     // 08 - { return voice; }

		[[nodiscard]] constexpr bool AffectsStealthMeter() const noexcept { return actorData.actorBaseFlags.none(ACTOR_BASE_DATA::Flag::kDoesntAffectStealthMeter); }
		[[nodiscard]] constexpr bool Bleeds() const noexcept { return actorData.actorBaseFlags.none(ACTOR_BASE_DATA::Flag::kDoesntBleed); }
		[[nodiscard]] constexpr bool IsEssential() const noexcept { return actorData.actorBaseFlags.all(ACTOR_BASE_DATA::Flag::kEssential); }
		[[nodiscard]] constexpr bool IsFemale() const noexcept { return actorData.actorBaseFlags.all(ACTOR_BASE_DATA::Flag::kFemale); }
		[[nodiscard]] inline bool    IsGhost() const { return GetIsGhost(); }
		[[nodiscard]] constexpr bool IsPreset() const noexcept { return actorData.actorBaseFlags.all(ACTOR_BASE_DATA::Flag::kIsChargenFacePreset); }
		[[nodiscard]] constexpr bool IsProtected() const noexcept { return actorData.actorBaseFlags.all(ACTOR_BASE_DATA::Flag::kProtected); }
		[[nodiscard]] constexpr bool IsSimpleActor() const noexcept { return actorData.actorBaseFlags.all(ACTOR_BASE_DATA::Flag::kSimpleActor); }
		[[nodiscard]] constexpr bool IsSummonable() const noexcept { return actorData.actorBaseFlags.all(ACTOR_BASE_DATA::Flag::kSummonable); }
		[[nodiscard]] constexpr bool IsUnique() const noexcept { return actorData.actorBaseFlags.all(ACTOR_BASE_DATA::Flag::kUnique); }
		[[nodiscard]] inline bool    IsInvulnerable() const { return GetInvulnerable(); }
		[[nodiscard]] constexpr bool HasAutoCalcStats() const noexcept { return actorData.actorBaseFlags.all(ACTOR_BASE_DATA::Flag::kAutoCalcStats); }
		[[nodiscard]] constexpr bool HasBleedoutOverride() const noexcept { return actorData.actorBaseFlags.all(ACTOR_BASE_DATA::Flag::kBleedoutOverride); }
		[[nodiscard]] constexpr bool HasPCLevelMult() const noexcept { return actorData.actorBaseFlags.all(ACTOR_BASE_DATA::Flag::kPCLevelMult); }
		[[nodiscard]] constexpr bool Respawns() const noexcept { return actorData.actorBaseFlags.all(ACTOR_BASE_DATA::Flag::kRespawn); }
		[[nodiscard]] constexpr bool UsesOppositeGenderAnims() const noexcept { return actorData.actorBaseFlags.all(ACTOR_BASE_DATA::Flag::kOppositeGenderAnims); }
		[[nodiscard]] constexpr bool UsesTemplate() const noexcept { return actorData.actorBaseFlags.all(ACTOR_BASE_DATA::Flag::kUsesTemplate); }

		[[nodiscard]] std::uint16_t GetLevel() const
		{
			using func_t = decltype(&TESActorBaseData::GetLevel);
			REL::Relocation<func_t> func{ RELOCATION_ID(14262, 14384) };
			return func(this);
		}

		// members
		ACTOR_BASE_DATA        actorData;         // 08
		TESLevItem*            deathItem;         // 20 - INAM
		BGSVoiceType*          voiceType;         // 28 - VTCK
		TESForm*               baseTemplateForm;  // 30 - TPLT
		TESForm**              templateForms;     // 38
		BSTArray<FACTION_RANK> factions;          // 40
	};
	static_assert(sizeof(TESActorBaseData) == 0x58);
}
