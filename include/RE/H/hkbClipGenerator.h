#pragma once

#include "RE/H/hkQsTransform.h"
#include "RE/H/hkaDefaultAnimationControl.h"
#include "RE/H/hkbContext.h"
#include "RE/H/hkbEventBase.h"
#include "RE/H/hkbEventProperty.h"
#include "RE/H/hkbGenerator.h"

namespace RE
{
	class hkClipTrigger
	{
	public:
		float            localTime;            // 00
		hkbEventProperty event;                // 08
		bool             relativeToEndOfClip;  // 18
		bool             acyclic;              // 19
		bool             isAnnotation;         // 1A
	};
	static_assert(sizeof(hkClipTrigger) == 0x20);

	class hkbClipTriggerArray : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbClipTriggerArray;
		inline static constexpr auto VTABLE = VTABLE_hkbClipTriggerArray;

		hkbClipTriggerArray() { stl::emplace_vtable(this); }
		~hkbClipTriggerArray() override;  // 00

		HK_HEAP_REDEFINE_NEW();

		// members
		hkArray<hkClipTrigger> triggers;  // 10
	};
	static_assert(sizeof(hkbClipTriggerArray) == 0x20);

	class hkbClipGenerator : public hkbGenerator
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbClipGenerator;
		inline static constexpr auto VTABLE = VTABLE_hkbClipGenerator;

		// Playback modes determine how time advances for the clip
		enum PlaybackMode
		{
			// Play the clip once from start to finish
			kModeSinglePlay = 0,
			// Play the clip over and over in a loop
			kModeLooping = 1,
			// Don't advance the clip. Let the user control the local time.
			kModeUserControlled = 2,
			// At the end of the animation, turn around backward, and then turn around again at the beginning, etc
			kModePingPong = 3,
			// How many modes there are
			kModeCount = 4
		};

		// Internal storage for each echo.
		struct Echo
		{
			char unk[0x10];  // 00
		};
		static_assert(sizeof(Echo) == 0x10);

		static const hkClass& StaticClass();

		hkbClipGenerator();
		~hkbClipGenerator() override = default;  // 00

		HK_HEAP_REDEFINE_NEW();

		// override (hkReferencedObject)
		const hkClass* GetClassType() const override;                                                                     // 01
		void           CalcContentStatistics(hkStatisticsCollector* a_collector, const hkClass* a_class) const override;  // 02

		// override (hkbNode)
		void                Activate(const hkbContext& a_context) override;                      // 04
		void                Update(const hkbContext& a_context, float a_timestep) override;      // 05
		void                Deactivate(const hkbContext& a_context) override;                    // 07
		bool                IsValid(hkStringPtr& err) const override;                            // 0A
		hkbNode*            CloneNode(hkbBehaviorGraph& rootBehavior) const override;            // 0C
		hkReferencedObject* CreateInternalState() override;                                      // 0D
		void                GetInternalState(hkReferencedObject& internalState) const override;  // 0E
		void                SetInternalState(const hkReferencedObject& internalState) override;  // 10

		// override (hkbGenerator)
		void Generate(const hkbContext& a_context, const hkbGeneratorOutput** activeChildrenOutput, hkbGeneratorOutput& output, float timeOffset = 0.0f) const override;  // 17
		void UpdateSync(const hkbContext& a_context, hkbNodeInfo& info) override;                                                                                         // 19
		void SetLocalTime(float time) override;                                                                                                                           // 1A
		void StartEcho() override;                                                                                                                                        // 1B

		// Add a trigger to the clip.
		void AddTrigger(float atLocalTime, const hkbEventBase& event, bool relativeToEndOfClip = false, bool acyclic = false, bool isAnnotation = false);

		/// Returns the duration of the clip in local time.  DEPRECATED.
		///
		/// This is the intrinsic duration of the animation, factoring in cropping, but not
		/// the playback speed.
		float GetDurationLocalTime() const;

		// members
		hkStringPtr                             animationName;                              // 048 - The name of the animation to play
		hkRefPtr<hkbClipTriggerArray>           triggers;                                   // 050 - Triggers (events that occur at specific times)
		float                                   cropStartAmountLocalTime{ 0 };              // 058 - The number of seconds (in clip time) to crop the beginning of the clip
		float                                   cropEndAmountLocalTime{ 0 };                // 05C - The number of seconds (in clip time) to crop the end of the clip
		float                                   startTime{ 0 };                             // 060 - The time at which to start the animation in local time
		float                                   playbackSpeed{ 1.0f };                      // 064 - Playback speed (negative for backward)
		float                                   enforcedDuration{ 0.f };                    // 068 - If m_enforcedDuration is greater than zero, the clip will be scaled to have the enforced duration
		float                                   userControlledTimeFraction{ 0.f };          // 06C - In user controlled mode, this fraction (between 0 and 1) dictates the time of the animation
		std::int16_t                            animationBindingIndex{ -1 };                // 070 - An index into the character's hkbAnimationBindingSet
		stl::enumeration<PlaybackMode, uint8_t> mode{ PlaybackMode::kModeLooping };         // 072 - The playback mode
		std::uint8_t                            flags{ 0 };                                 // 073 - Flags for specialized behavior
		std::uint32_t                           unk74;                                      // 074 - pad?
		hkArray<hkRefVariant>                   animDatas;                                  // 078
		hkRefPtr<hkaDefaultAnimationControl>    animationControl;                           // 088
		hkRefPtr<hkbClipTriggerArray>           originalTriggers;                           // 090
		hkaDefaultAnimationControlMapperData*   mapperData{ nullptr };                      // 098 - The retargeting skeleton mapper data
		hkaAnimationBinding*                    binding{ nullptr };                         // 0A0 - The animation binding. This is stored for easy access for SPUs.
		hkRefPtr<hkReferencedObject>            mirroredAnimation;                          // 0A8
		hkQsTransform                           extractedMotion;                            // 0B0 - The motion extracted in the last update
		hkArray<Echo>                           echos;                                      // 0E0 - The list of active echos
		float                                   localTime{ 0.f };                           // 0F0 - The local time of the clip (excactly as set in the animation control)
		float                                   time{ 0.f };                                // 0F4 - The time lapsed since activate, taking into consideration the playback speed
		float                                   previousUserControlledTimeFraction{ 0.f };  // 0F8 - In user controlled mode, this fraction (between 0 and 1) is the time of the animation in the previous update
		std::int32_t                            bufferSize{ 0 };                            // 0FC - The buffer size to use when decompressing animations (use getMaxSizeOfCombinedDataChunks())
		std::int32_t                            echoBufferSize{ 0 };                        // 100
		bool                                    atEnd{ false };                             // 104 - This tells us whether we have reached the end of the clip in MODE_SINGLE_PLAY
		bool                                    ignoreStartTime{ false };                   // 105 - The start time to use next time time activate() is called
		bool                                    pingPongBackward{ false };                  // 106 - Whether ping-pong mode is currently going backward
		std::uint8_t                            pad107[9];                                  // 107
	};
	static_assert(sizeof(hkbClipGenerator) == 0x110);
}
