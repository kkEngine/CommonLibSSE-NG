#include "RE/B/BSMultiBoundNode.h"

using namespace REL;

namespace RE
{
	BSMultiBoundRoom* BSMultiBoundNode::GetMultiBoundRoom()
	{
		return RelocateVirtual<decltype(&BSMultiBoundNode::GetMultiBoundRoom)>(0x3E, this);
	}

	bool BSMultiBoundNode::QPointWithin(const NiPoint3& a_point)
	{
		return RelocateVirtual<decltype(&BSMultiBoundNode::QPointWithin)>(0x3F, this, a_point);
	}

	void BSMultiBoundNode::Unk_40()
	{
		RelocateVirtual<decltype(&BSMultiBoundNode::Unk_40)>(0x40, this);
	}

	void BSMultiBoundNode::Unk_41()
	{
		RelocateVirtual<decltype(&BSMultiBoundNode::Unk_41)>(0x41, this);
	}
}
