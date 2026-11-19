#pragma once

namespace RE
{
	// AE 1.7.99+ only. PlayerCharacter listens for it (BSTEventSink<BSSystemEvent> at 0x2D8).
	class BSSystemEvent
	{
	public:
		// members
		std::uint64_t unk00;  // 00
		std::uint64_t unk08;  // 08
		std::uint32_t unk10;  // 10
	};
	static_assert(sizeof(BSSystemEvent) == 0x18);
}
