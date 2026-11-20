#pragma once

#include "RE/B/BSTrackedControllerDevice.h"

namespace RE
{
	class BSOpenVRControllerDevice : public BSTrackedControllerDevice
	{
	public:

		~BSOpenVRControllerDevice() override;

		// override BSIInputDevice
		void               Initialize() override;                                                  // 01
		void               Process(float a_arg1) override;                                         // 02
		void               Release() override;                                                     // 03 - { return; }
		bool               GetKeyMapping(std::uint32_t a_key, BSFixedString& a_mapping) override;  // 04
		std::uint32_t      GetMappingKey(BSFixedString a_mapping) override;                        // 05
		bool               GetMappedKeycode(std::uint32_t a_key, std::uint32_t& outKeyCode) override;  // 06
		[[nodiscard]] bool IsEnabled() const override;                                             // 07 - { return true; }
		void               Reset() override;                                                       // 08

	private:
	};
}
