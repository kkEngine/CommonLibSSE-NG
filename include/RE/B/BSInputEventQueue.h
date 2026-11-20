#pragma once

#include "RE/B/BSTSingleton.h"
#include "RE/B/ButtonEvent.h"
#include "RE/C/CharEvent.h"
#include "RE/D/DeviceConnectEvent.h"
#include "RE/K/KinectEvent.h"
#include "RE/M/MouseMoveEvent.h"
#include "RE/T/ThumbstickEvent.h"
#	include "RE/A/AmiiboEvent.h"
#	include "RE/M/MotionGestureEvent.h"
#	include "RE/S/SixaxisEvent.h"

namespace RE
{
	class BSInputEventQueue : public BSTSingletonSDM<BSInputEventQueue>
	{
	public:
		inline static constexpr std::uint8_t MAX_BUTTON_EVENTS = 10;
		inline static constexpr std::uint8_t MAX_CHAR_EVENTS = 5;
		inline static constexpr std::uint8_t MAX_MOUSE_EVENTS = 1;
		inline static constexpr std::uint8_t MAX_THUMBSTICK_EVENTS = 2;
		inline static constexpr std::uint8_t MAX_CONNECT_EVENTS = 1;
		inline static constexpr std::uint8_t MAX_KINECT_EVENTS = 1;
		inline static constexpr std::uint8_t MAX_SIXAXIS_EVENTS = 2;
		inline static constexpr std::uint8_t MAX_MOTION_GESTURE_EVENTS = 2;
		inline static constexpr std::uint8_t MAX_AMIIBO_EVENTS = 1;

		static BSInputEventQueue* GetSingleton();

		void AddButtonEvent(INPUT_DEVICE a_device, std::int32_t a_id, float a_value, float a_duration);
		void AddCharEvent(std::uint32_t a_keyCode);
		void AddMouseMoveEvent(std::int32_t a_mouseInputX, std::int32_t a_mouseInputY);
		void AddThumbstickEvent(ThumbstickEvent::InputType a_id, float a_xValue, float a_yValue);
		void AddConnectEvent(INPUT_DEVICE a_device, bool a_connected);
		void AddKinectEvent(const BSFixedString& a_userEvent, const BSFixedString& a_heard);
		void PushOntoInputQueue(InputEvent* a_event);
		void ClearInputQueue();

		// members
		std::uint8_t       pad001;                                   // 001
		std::uint16_t      pad002;                                   // 002
		std::uint32_t      buttonEventCount;                         // 004
		std::uint32_t      charEventCount;                           // 008
		std::uint32_t      mouseEventCount;                          // 00C
		std::uint32_t      thumbstickEventCount;                     // 010
		std::uint32_t      connectEventCount;                        // 014
		std::uint32_t      kinectEventCount;                         // 018
		// AE 1.7.99 added three event queues, the arrays below moved by 8
		std::uint32_t      sixaxisEventCount;                        // 01C
		std::uint32_t      motionGestureEventCount;                  // 020
		std::uint32_t      amiiboEventCount;                         // 024
		ButtonEvent        buttonEvents[MAX_BUTTON_EVENTS];          // 028
		CharEvent          charEvents[MAX_CHAR_EVENTS];              // 208
		MouseMoveEvent     mouseEvents[MAX_MOUSE_EVENTS];            // 2A8
		ThumbstickEvent    thumbstickEvents[MAX_THUMBSTICK_EVENTS];  // 2D8
		DeviceConnectEvent connectEvents[MAX_CONNECT_EVENTS];        // 338
		KinectEvent        kinectEvents[MAX_KINECT_EVENTS];          // 358
		SixaxisEvent       sixaxisEvents[MAX_SIXAXIS_EVENTS];        // 388
		MotionGestureEvent motionGestureEvents[MAX_MOTION_GESTURE_EVENTS];  // 4A8
		AmiiboEvent        amiiboEvents[MAX_AMIIBO_EVENTS];          // 518
		InputEvent*        queueHead;                                // 558
		InputEvent*        queueTail;                                // 560
	};
	static_assert(offsetof(BSInputEventQueue, queueHead) == 0x558);
	static_assert(sizeof(BSInputEventQueue) == 0x568);
}
