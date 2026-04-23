#include "RE/H/hkMemoryRouter.h"

#include "RE/H/hkMemoryAllocator.h"

namespace RE
{
	hkMemoryRouter& hkMemoryRouter::getInstance()
	{
		return *getInstancePtr();
	}

	hkMemoryRouter* hkMemoryRouter::getInstancePtr()
	{
		return static_cast<hkMemoryRouter*>(REX::W32::TlsGetValue(s_memoryRouter()));
	}

	void* hkMemoryRouter::easyAlloc(hkMemoryAllocator& b, int32_t nbytes)
	{
		char* ans = static_cast<char*>(b.BlockAlloc(nbytes + 16));
		*reinterpret_cast<hkMemoryAllocator**>(ans) = &b;
		*reinterpret_cast<int32_t*>(ans + 8) = nbytes;
		return ans + 16;
	}

	void hkMemoryRouter::easyFree(hkMemoryAllocator& b, void* p)
	{
		if (!p)
			return;

		char*               p_ = static_cast<char*>(p);
		int32_t             size = *reinterpret_cast<int32_t*>(p_ - 8);
		hkMemoryAllocator** p_alloc = reinterpret_cast<hkMemoryAllocator**>(p_ - 16);
		*p_alloc = nullptr;
		b.BlockFree(p_alloc, size + 16);
	}

	uint32_t hkMemoryRouter::s_memoryRouter()
	{
		return *REL::Relocation<uint32_t*>(RELOCATION_ID(520865, 407383));
	}
}
