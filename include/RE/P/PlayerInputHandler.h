#pragma once

namespace RE
{
	class ButtonEvent;
	class InputEvent;
	class MotionGestureEvent;
	class MouseMoveEvent;
	class PlayerControlsData;
	class SixaxisEvent;
	class ThumbstickEvent;

	class PlayerInputHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_PlayerInputHandler;

		virtual ~PlayerInputHandler();  // 00

		virtual bool CanProcess(InputEvent* a_event) = 0;  // 01
		// AE 1.7.99 inserted two event handlers here, every vfunc below moved by 2
		virtual void ProcessMotionGesture(MotionGestureEvent* a_event, PlayerControlsData* a_data);  // 02 - { return; }
		virtual void ProcessSixaxis(SixaxisEvent* a_event, PlayerControlsData* a_data);              // 03 - { return; }
		virtual void ProcessThumbstick(ThumbstickEvent* a_event, PlayerControlsData* a_data);        // 04 - { return; }
		virtual void ProcessMouseMove(MouseMoveEvent* a_event, PlayerControlsData* a_data);          // 05 - { return; }
		virtual void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data);                // 06 - { return; }

		[[nodiscard]] bool IsInputEventHandlingEnabled() const;
		void               SetInputEventHandlingEnabled(bool a_enabled);

		// members
		bool          inputEventHandlingEnabled;  // 08
		std::uint8_t  pad09;                      // 09
		std::uint16_t pad0A;                      // 0A
		std::uint32_t pad0C;                      // 0C
	};
	static_assert(sizeof(PlayerInputHandler) == 0x10);
}
