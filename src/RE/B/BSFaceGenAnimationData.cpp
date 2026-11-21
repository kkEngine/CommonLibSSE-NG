#include "RE/B/BSFaceGenAnimationData.h"

namespace RE
{
	namespace
	{
		constexpr float pi_180 = 0.0174532925f;

		float rand(float a_min, float a_max)
		{
			return a_min + (a_max - a_min) * (static_cast<float>(std::rand()) / RAND_MAX);
		}

		float rand(float a_min, float a_max, float a_exp)
		{
			return a_min + (a_max - a_min) * pow(static_cast<float>(std::rand()) / RAND_MAX, a_exp);
		}

		float deg2rad(float a_degrees)
		{
			return a_degrees * pi_180;
		}

		struct Settings
		{
			struct EyesBlinking
			{
				float fBlinkDownTime{ 0.04f };
				float fBlinkUpTime{ 0.14f };
				float fBlinkDelayMin{ 0.5f };
				float fBlinkDelayMax{ 8.0f };
			};

			struct EyesMovement
			{
				float fTrackSpeed{ 5.0f };
				float fTrackEyeXY{ 28.0f };
				float fTrackEyeZ{ 20.0f };
				float fEyeHeadingMinOffsetEmotionAngry{ -0.05f };
				float fEyeHeadingMaxOffsetEmotionAngry{ 0.05f };
				float fEyePitchMinOffsetEmotionAngry{ -0.05f };
				float fEyePitchMaxOffsetEmotionAngry{ 0.1f };
				float fEyeOffsetDelayMinEmotionAngry{ 0.5f };
				float fEyeOffsetDelayMaxEmotionAngry{ 3.0f };
				float fEyeHeadingMinOffsetEmotionHappy{ -0.1f };
				float fEyeHeadingMaxOffsetEmotionHappy{ 0.1f };
				float fEyePitchMinOffsetEmotionHappy{ -0.05f };
				float fEyePitchMaxOffsetEmotionHappy{ 0.1f };
				float fEyeOffsetDelayMinEmotionHappy{ 0.5f };
				float fEyeOffsetDelayMaxEmotionHappy{ 4.0f };
				float fEyeHeadingMinOffsetEmotionSurprise{ -0.1f };
				float fEyeHeadingMaxOffsetEmotionSurprise{ 0.1f };
				float fEyePitchMinOffsetEmotionSurprise{ -0.05f };
				float fEyePitchMaxOffsetEmotionSurprise{ 0.1f };
				float fEyeOffsetDelayMinEmotionSurprise{ 0.5f };
				float fEyeOffsetDelayMaxEmotionSurprise{ 4.0f };
				float fEyeHeadingMinOffsetEmotionSad{ -0.1f };
				float fEyeHeadingMaxOffsetEmotionSad{ 0.1f };
				float fEyePitchMinOffsetEmotionSad{ -0.05f };
				float fEyePitchMaxOffsetEmotionSad{ -0.015f };
				float fEyeOffsetDelayMinEmotionSad{ 2.0f };
				float fEyeOffsetDelayMaxEmotionSad{ 3.0f };
				float fEyeHeadingMinOffsetEmotionFear{ -0.1f };
				float fEyeHeadingMaxOffsetEmotionFear{ 0.1f };
				float fEyePitchMinOffsetEmotionFear{ 0.01f };
				float fEyePitchMaxOffsetEmotionFear{ 0.01f };
				float fEyeOffsetDelayMinEmotionFear{ 0.5f };
				float fEyeOffsetDelayMaxEmotionFear{ 1.5f };
				float fEyeHeadingMinOffsetEmotionNeutral{ -0.1f };
				float fEyeHeadingMaxOffsetEmotionNeutral{ 0.1f };
				float fEyePitchMinOffsetEmotionNeutral{ -0.025f };
				float fEyePitchMaxOffsetEmotionNeutral{ 0.1f };
				float fEyeOffsetDelayMinEmotionNeutral{ 0.5f };
				float fEyeOffsetDelayMaxEmotionNeutral{ 4.0f };
				float fEyeHeadingMinOffsetEmotionPuzzled{ 0.0f };
				float fEyeHeadingMaxOffsetEmotionPuzzled{ 0.0f };
				float fEyePitchMinOffsetEmotionPuzzled{ 0.0f };
				float fEyePitchMaxOffsetEmotionPuzzled{ 0.0f };
				float fEyeOffsetDelayMinEmotionPuzzled{ 3.0f };
				float fEyeOffsetDelayMaxEmotionPuzzled{ 3.0f };
				float fEyeHeadingMinOffsetEmotionDisgusted{ 0.0f };
				float fEyeHeadingMaxOffsetEmotionDisgusted{ 0.0f };
				float fEyePitchMinOffsetEmotionDisgusted{ 0.0f };
				float fEyePitchMaxOffsetEmotionDisgusted{ 0.0f };
				float fEyeOffsetDelayMinEmotionDisgusted{ 3.0f };
				float fEyeOffsetDelayMaxEmotionDisgusted{ 3.0f };
				float fEyeHeadingMinOffsetEmotionCombatAnger{ 0.0f };
				float fEyeHeadingMaxOffsetEmotionCombatAnger{ 0.0f };
				float fEyePitchMinOffsetEmotionCombatAnger{ 0.0f };
				float fEyePitchMaxOffsetEmotionCombatAnger{ 0.0f };
				float fEyeOffsetDelayMinEmotionCombatAnger{ 3.0f };
				float fEyeOffsetDelayMaxEmotionCombatAnger{ 3.0f };
				float fEyeHeadingMinOffsetEmotionCombatShout{ 0.0f };
				float fEyeHeadingMaxOffsetEmotionCombatShout{ 0.0f };
				float fEyePitchMinOffsetEmotionCombatShout{ 0.0f };
				float fEyePitchMaxOffsetEmotionCombatShout{ 0.0f };
				float fEyeOffsetDelayMinEmotionCombatShout{ 3.0f };
				float fEyeOffsetDelayMaxEmotionCombatShout{ 3.0f };
			};
		};

		static Settings::EyesBlinking s_defaultEyesBlinking;
		static Settings::EyesMovement s_defaultEyesMovement;
	}

	void BSFaceGenAnimationData::SetExpressionOverride(std::uint32_t a_idx, float a_value)
	{
		using func_t = decltype(&BSFaceGenAnimationData::SetExpressionOverride);
		REL::Relocation<func_t> func(RELOCATION_ID(0, 26594));
		func(this, a_idx, a_value);
	}

	void BSFaceGenAnimationData::ClearExpressionOverride()
	{
		expressionOverride = false;
	}

	void BSFaceGenAnimationData::Reset(float a_timer, bool a_resetExpression, bool a_resetModifierAndPhoneme, bool a_resetCustom, bool a_closeEyes)
	{
		using func_t = decltype(&BSFaceGenAnimationData::Reset);
		REL::Relocation<func_t> func{ RELOCATION_ID(25977, 26586) };
		return func(this, a_timer, a_resetExpression, a_resetModifierAndPhoneme, a_resetCustom, a_closeEyes);
	}

	std::uint32_t BSFaceGenAnimationData::GetActiveExpression() const
	{
		std::uint32_t expression = Expression::MoodNeutral;

		for (std::uint32_t i = 0; i < expression3.count; ++i) {
			if (expression3.values[i] > expression3.values[expression]) {
				expression = i;
			}
		}

		return expression;
	}

	void BSFaceGenAnimationData::DialogueModifiersUpdate(float a_timeDelta)
	{
		if (!dialogueData || (((dialogueData->refCount & 0x70000000) + 0xD0000000) & 0xEFFFFFFF) != 0) {
			return;
		}

		REL::Relocation<bool(void*, float, float*)> sub_1FCD10{ REL::ID(16267) };

		modifierDialogueKeyFrame.timer += a_timeDelta;
		sub_1FCD10(dialogueData->unk28, modifierDialogueKeyFrame.timer, modifierDialogueKeyFrame.values);
	}

	void BSFaceGenAnimationData::DialoguePhonemesUpdate(float a_timeDelta)
	{
		if (!dialogueData || (((dialogueData->refCount & 0x70000000) + 0xD0000000) & 0xEFFFFFFF) != 0) {
			return;
		}

		REL::Relocation<bool(void*, float, float*)> sub_1FC9B0{ REL::ID(16266) };

		phoneme1.timer += a_timeDelta;
		sub_1FC9B0(dialogueData->unk28, phoneme1.timer, phoneme1.values);
	}

	void BSFaceGenAnimationData::CheckAndReleaseDialogueData()
	{
		if (!dialogueData || (((dialogueData->refCount & 0x70000000) + 0xD0000000) & 0xEFFFFFFF) != 0) {
			return;
		}

		auto timer = (dialogueData->unk28->unk0 + (dialogueData->unk28->unk4 < 0 ? -dialogueData->unk28->unk4 : 0)) * 0.033f + 0.2f;

		if (phoneme1.timer <= timer) {
			return;
		}

		REL::Relocation<void(void*)> ReleaseDialogueData{ REL::ID(16318) };

		ReleaseDialogueData(dialogueData);

		dialogueData = nullptr;
	}

	void BSFaceGenAnimationData::EyesBlinkingUpdate(float a_timeDelta)
	{
		eyesBlinkingTimer = std::max(eyesBlinkingTimer - a_timeDelta, 0.0f);
		auto blinkValue = 0.0f;

		switch (eyesBlinkingStage) {
		case EyesBlinkingStage::BlinkDelay:
			{
				blinkValue = 0.0f;

				if (eyesBlinkingTimer == 0.0f) {
					eyesBlinkingStage = EyesBlinkingStage::BlinkDown;
					eyesBlinkingTimer = s_defaultEyesBlinking.fBlinkDownTime;
				}

				break;
			}
		case EyesBlinkingStage::BlinkDown:
			{
				blinkValue = s_defaultEyesBlinking.fBlinkDownTime != 0.0f ? 1.0f - eyesBlinkingTimer / s_defaultEyesBlinking.fBlinkDownTime : 1.0f;

				if (eyesBlinkingTimer == 0.0f) {
					eyesBlinkingStage = EyesBlinkingStage::BlinkUp;
					eyesBlinkingTimer = s_defaultEyesBlinking.fBlinkUpTime;
				}

				break;
			}
		case EyesBlinkingStage::BlinkUp:
			{
				blinkValue = s_defaultEyesBlinking.fBlinkUpTime != 0.0f ? eyesBlinkingTimer / s_defaultEyesBlinking.fBlinkUpTime : 0.0f;

				if (eyesBlinkingTimer == 0.0f) {
					eyesBlinkingStage = EyesBlinkingStage::BlinkDelay;
					eyesBlinkingTimer = rand(s_defaultEyesBlinking.fBlinkDelayMin, s_defaultEyesBlinking.fBlinkDelayMax, 2.0f);
				}

				break;
			}
		case EyesBlinkingStage::BlinkDownAndWait1:
			{
				if (unk21A) {
					blinkValue = s_defaultEyesBlinking.fBlinkDownTime != 0.0f ? 1.0f - eyesBlinkingTimer / s_defaultEyesBlinking.fBlinkDownTime : 1.0f;
				} else {
					blinkValue = 1.0f;
					eyesBlinkingStage = EyesBlinkingStage::BlinkUp;
					eyesBlinkingTimer = s_defaultEyesBlinking.fBlinkUpTime;
				}

				break;
			}
		case EyesBlinkingStage::BlinkDownAndWait2:
			{
				eyesBlinkingStage = EyesBlinkingStage::BlinkDownAndWait1;

				break;
			}
		default:
			{
				blinkValue = 0.0f;
				eyesBlinkingStage = EyesBlinkingStage::BlinkDelay;
				eyesBlinkingTimer = rand(s_defaultEyesBlinking.fBlinkDelayMin, s_defaultEyesBlinking.fBlinkDelayMax, 2.0f);

				break;
			}
		}

		blinkValue = std::clamp(blinkValue, 0.0f, 1.0f);

		modifier3.values[Modifier::BlinkLeft] = blinkValue;
		modifier3.values[Modifier::BlinkRight] = blinkValue;
	}

	void BSFaceGenAnimationData::EyesMovementUpdate(float a_timeDelta)
	{
		eyesOffsetTimer = std::max(eyesOffsetTimer - a_timeDelta, 0.0f);

		if (eyesOffsetTimer > 0.0f) {
			return;
		}

		switch (GetActiveExpression()) {
		case Expression::DialogueAnger:
		case Expression::MoodAnger:
			{
				eyesOffsetTimer = rand(s_defaultEyesMovement.fEyeOffsetDelayMinEmotionAngry, s_defaultEyesMovement.fEyeOffsetDelayMaxEmotionAngry, 2.0f);
				eyesHeadingOffset = rand(s_defaultEyesMovement.fEyeHeadingMinOffsetEmotionAngry, s_defaultEyesMovement.fEyeHeadingMaxOffsetEmotionAngry);
				eyesPitchOffset = rand(s_defaultEyesMovement.fEyePitchMinOffsetEmotionAngry, s_defaultEyesMovement.fEyePitchMaxOffsetEmotionAngry);

				break;
			}
		case Expression::DialogueHappy:
		case Expression::MoodHappy:
			{
				eyesOffsetTimer = rand(s_defaultEyesMovement.fEyeOffsetDelayMinEmotionHappy, s_defaultEyesMovement.fEyeOffsetDelayMaxEmotionHappy, 0.5f);
				eyesHeadingOffset = rand(s_defaultEyesMovement.fEyeHeadingMinOffsetEmotionHappy, s_defaultEyesMovement.fEyeHeadingMaxOffsetEmotionHappy);
				eyesPitchOffset = rand(s_defaultEyesMovement.fEyePitchMinOffsetEmotionHappy, s_defaultEyesMovement.fEyePitchMaxOffsetEmotionHappy);

				break;
			}
		case Expression::DialogueSurprise:
		case Expression::MoodSurprise:
			{
				eyesOffsetTimer = rand(s_defaultEyesMovement.fEyeOffsetDelayMinEmotionSurprise, s_defaultEyesMovement.fEyeOffsetDelayMaxEmotionSurprise, 0.5f);
				eyesHeadingOffset = rand(s_defaultEyesMovement.fEyeHeadingMinOffsetEmotionSurprise, s_defaultEyesMovement.fEyeHeadingMaxOffsetEmotionSurprise);
				eyesPitchOffset = rand(s_defaultEyesMovement.fEyePitchMinOffsetEmotionSurprise, s_defaultEyesMovement.fEyePitchMaxOffsetEmotionSurprise);

				break;
			}
		case Expression::DialogueSad:
		case Expression::MoodSad:
			{
				eyesOffsetTimer = rand(s_defaultEyesMovement.fEyeOffsetDelayMinEmotionSad, s_defaultEyesMovement.fEyeOffsetDelayMaxEmotionSad);
				eyesHeadingOffset = rand(s_defaultEyesMovement.fEyeHeadingMinOffsetEmotionSad, s_defaultEyesMovement.fEyeHeadingMaxOffsetEmotionSad);
				eyesPitchOffset = rand(s_defaultEyesMovement.fEyePitchMinOffsetEmotionSad, s_defaultEyesMovement.fEyePitchMaxOffsetEmotionSad);

				break;
			}
		case Expression::DialogueFear:
		case Expression::MoodFear:
			{
				eyesOffsetTimer = rand(s_defaultEyesMovement.fEyeOffsetDelayMinEmotionFear, s_defaultEyesMovement.fEyeOffsetDelayMaxEmotionFear);
				eyesHeadingOffset = rand(0.0f, 1.0f) <= 0.5f ? 0.0f : rand(s_defaultEyesMovement.fEyeHeadingMinOffsetEmotionFear, s_defaultEyesMovement.fEyeHeadingMaxOffsetEmotionFear);
				eyesPitchOffset = rand(0.0f, 1.0f) <= 0.5f ? 0.0f : rand(s_defaultEyesMovement.fEyePitchMinOffsetEmotionFear, s_defaultEyesMovement.fEyePitchMaxOffsetEmotionFear);

				break;
			}
		case Expression::DialoguePuzzled:
		case Expression::MoodPuzzled:
			{
				eyesOffsetTimer = rand(s_defaultEyesMovement.fEyeOffsetDelayMinEmotionPuzzled, s_defaultEyesMovement.fEyeOffsetDelayMaxEmotionPuzzled);
				eyesHeadingOffset = rand(s_defaultEyesMovement.fEyeHeadingMinOffsetEmotionPuzzled, s_defaultEyesMovement.fEyeHeadingMaxOffsetEmotionPuzzled);
				eyesPitchOffset = rand(s_defaultEyesMovement.fEyePitchMinOffsetEmotionPuzzled, s_defaultEyesMovement.fEyePitchMaxOffsetEmotionPuzzled);

				break;
			}
		case Expression::DialogueDisgusted:
		case Expression::MoodDisgusted:
			{
				eyesOffsetTimer = rand(s_defaultEyesMovement.fEyeOffsetDelayMinEmotionDisgusted, s_defaultEyesMovement.fEyeOffsetDelayMaxEmotionDisgusted);
				eyesHeadingOffset = rand(s_defaultEyesMovement.fEyeHeadingMinOffsetEmotionDisgusted, s_defaultEyesMovement.fEyeHeadingMaxOffsetEmotionDisgusted);
				eyesPitchOffset = rand(s_defaultEyesMovement.fEyePitchMinOffsetEmotionDisgusted, s_defaultEyesMovement.fEyePitchMaxOffsetEmotionDisgusted);

				break;
			}
		case Expression::CombatAnger:
			{
				eyesOffsetTimer = rand(s_defaultEyesMovement.fEyeOffsetDelayMinEmotionCombatAnger, s_defaultEyesMovement.fEyeOffsetDelayMaxEmotionCombatAnger);
				eyesHeadingOffset = rand(s_defaultEyesMovement.fEyeHeadingMinOffsetEmotionCombatAnger, s_defaultEyesMovement.fEyeHeadingMaxOffsetEmotionCombatAnger);
				eyesPitchOffset = rand(s_defaultEyesMovement.fEyePitchMinOffsetEmotionCombatAnger, s_defaultEyesMovement.fEyePitchMaxOffsetEmotionCombatAnger);

				break;
			}
		case Expression::CombatShout:
			{
				eyesOffsetTimer = rand(s_defaultEyesMovement.fEyeOffsetDelayMinEmotionCombatShout, s_defaultEyesMovement.fEyeOffsetDelayMaxEmotionCombatShout);
				eyesHeadingOffset = rand(s_defaultEyesMovement.fEyeHeadingMinOffsetEmotionCombatShout, s_defaultEyesMovement.fEyeHeadingMaxOffsetEmotionCombatShout);
				eyesPitchOffset = rand(s_defaultEyesMovement.fEyePitchMinOffsetEmotionCombatShout, s_defaultEyesMovement.fEyePitchMaxOffsetEmotionCombatShout);

				break;
			}
		default:
			{
				eyesOffsetTimer = rand(s_defaultEyesMovement.fEyeOffsetDelayMinEmotionNeutral, s_defaultEyesMovement.fEyeOffsetDelayMaxEmotionNeutral, 2.0f);
				eyesHeadingOffset = rand(s_defaultEyesMovement.fEyeHeadingMinOffsetEmotionNeutral, s_defaultEyesMovement.fEyeHeadingMaxOffsetEmotionNeutral);
				eyesPitchOffset = rand(s_defaultEyesMovement.fEyePitchMinOffsetEmotionNeutral, s_defaultEyesMovement.fEyePitchMaxOffsetEmotionNeutral);

				break;
			}
		}
	}

	void BSFaceGenAnimationData::EyesDirectionUpdate(float a_timeDelta)
	{
		auto eyesHeadingMax = deg2rad(s_defaultEyesMovement.fTrackEyeXY);
		auto eyesPitchMax = deg2rad(s_defaultEyesMovement.fTrackEyeZ);
		auto eyesHeadingDeltaMax = s_defaultEyesMovement.fTrackSpeed * a_timeDelta;
		auto eyesPitchDeltaMax = s_defaultEyesMovement.fTrackSpeed * a_timeDelta;

		eyesHeading = std::clamp(eyesHeadingBase + eyesHeadingOffset, eyesHeading - eyesHeadingDeltaMax, eyesHeading + eyesHeadingDeltaMax);
		eyesPitch = std::clamp(eyesPitchBase + eyesPitchOffset, eyesPitch - eyesPitchDeltaMax, eyesPitch + eyesPitchDeltaMax);
		eyesHeading = std::clamp(eyesHeading, -eyesHeadingMax, eyesHeadingMax);
		eyesPitch = std::clamp(eyesPitch, -eyesPitchMax, eyesPitchMax);

		modifier3.values[Modifier::LookLeft] = eyesHeading < 0.0f ? (eyesHeadingMax != 0.0f ? -eyesHeading / eyesHeadingMax : 0.0f) : 0.0f;
		modifier3.values[Modifier::LookRight] = eyesHeading > 0.0f ? (eyesHeadingMax != 0.0f ? eyesHeading / eyesHeadingMax : 0.0f) : 0.0f;
		modifier3.values[Modifier::LookDown] = eyesPitch < 0.0f ? (eyesPitchMax != 0.0f ? -eyesPitch / eyesPitchMax : 0.0f) : 0.0f;
		modifier3.values[Modifier::LookUp] = eyesPitch > 0.0f ? (eyesPitchMax != 0.0f ? eyesPitch / eyesPitchMax : 0.0f) : 0.0f;
	}

	bool BSFaceGenAnimationData::KeyframesUpdateHook(float a_timeDelta, bool a_updateBlinking)
	{
		RE::BSSpinLockGuard locker(lock);

		// expressions
		{
			auto merge = [](Keyframe& a_src, Keyframe& a_dst) {
				if (!a_src.IsZero()) {
					a_dst.Copy(&a_src);
				}
			};

			expression3.Reset();

			expressionKeyFrame.TransitionUpdate(a_timeDelta, transitionTargetKeyFrame);

			merge(expressionKeyFrame, expression3);
			merge(expression2, expression3);
		}

		// modifiers
		{
			auto merge = [](Keyframe& a_src, Keyframe& a_dst) {
				auto count = std::min(a_src.count, a_dst.count);
				for (std::uint32_t i = 0; i < count; ++i) {
					if (a_src.values[i] != 0.0f) {
						a_dst.values[i] = a_src.values[i];
					}
				}
				if (a_src.values[Modifier::LookDown] != 0.0f || a_src.values[Modifier::LookLeft] != 0.0f || a_src.values[Modifier::LookRight] != 0.0f || a_src.values[Modifier::LookUp] != 0.0f) {
					a_dst.values[Modifier::LookDown] = a_src.values[Modifier::LookDown];
					a_dst.values[Modifier::LookLeft] = a_src.values[Modifier::LookLeft];
					a_dst.values[Modifier::LookRight] = a_src.values[Modifier::LookRight];
					a_dst.values[Modifier::LookUp] = a_src.values[Modifier::LookUp];
				}
			};

			modifier3.Reset();

			DialogueModifiersUpdate(a_timeDelta);
			EyesBlinkingUpdate(a_timeDelta);

			merge(modifierDialogueKeyFrame, modifier3);

			if (!unk21A) {
				EyesMovementUpdate(a_timeDelta);
				EyesDirectionUpdate(a_timeDelta);
			}

			merge(modifierKeyFrame, modifier3);
		}

		// phonemes
		{
			auto merge = [](Keyframe& a_src, Keyframe& a_dst) {
				auto count = std::min(a_src.count, a_dst.count);
				for (std::uint32_t i = 0; i < count; ++i) {
					if (a_src.values[i] != 0.0f) {
						a_dst.values[i] = a_src.values[i];
					}
				}
			};

			phoneme3.Reset();

			DialoguePhonemesUpdate(a_timeDelta);

			merge(phoneme1, phoneme3);
			merge(phenomeKeyFrame, phoneme3);
		}

		// custom
		{
			auto merge = [](BSFaceGenKeyframeMultiple& a_src, BSFaceGenKeyframeMultiple& a_dst) {
				auto count = std::min(a_src.count, a_dst.count);
				for (std::uint32_t i = 0; i < count; ++i) {
					if (a_src.values[i] != 0.0f) {
						a_dst.values[i] = a_src.values[i];
					}
				}
			};

			custom3.Reset();

			merge(custom1, custom3);
			merge(customKeyFrame, custom3);
		}

		CheckAndReleaseDialogueData();

		unk217 = true;

		return unk217;
	}
}
