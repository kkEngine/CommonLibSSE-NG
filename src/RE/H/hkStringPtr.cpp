#include "RE/H/hkStringPtr.h"
#include <RE/H/hkMemoryRouter.h>

namespace RE
{
	hkStringPtr::hkStringPtr(const char* a_data) :
		_data(nullptr)
	{
		using func_t = std::add_pointer_t<void(hkStringPtr&, const char*)>;
		REL::Relocation<func_t> func{ RELOCATION_ID(56801, 57231) };
		func(*this, a_data);
	}

	hkStringPtr::hkStringPtr(const char* a_data, size_type len) :
		_data(nullptr)
	{
		assign(a_data, len, true);
	}

	hkStringPtr::hkStringPtr(const hkStringPtr& other) :
		_data(nullptr)
	{
		assign(other.data(), -1, true);
	}

	hkStringPtr::~hkStringPtr()
	{
		assign(nullptr, -1, true);
	}

	hkStringPtr& hkStringPtr::operator=(const char* s)
	{
		assign(s, -1, true);
		return *this;
	}

	hkStringPtr& hkStringPtr::operator=(const hkStringPtr& s)
	{
		assign(s.data(), -1, true);
		return *this;
	}

	void hkStringPtr::assign(const char* a_data, size_type len, bool copy)
	{
		if (data() == a_data)
			return;

		if (should_deallocate()) {
			hkMemoryRouter::easyFree(hkMemoryRouter::getInstance().heap(), const_cast<char*>(data()));
		}

		if (a_data) {
			if (copy) {
				if (len == -1) {
					_data = strDup(a_data) + 1;
				} else {
					_data = strNdup(a_data, len) + 1;
				}
			} else {
				_data = a_data;
			}
		} else {
			_data = nullptr;
		}
	}

	bool hkStringPtr::should_deallocate() const
	{
		return reinterpret_cast<std::uintptr_t>(_data) & kManaged;
	}

	char* hkStringPtr::strDup(const char* a_data)
	{
		auto data_len = std::strlen(a_data);
		auto ans = static_cast<char*>(hkMemoryRouter::easyAlloc(hkMemoryRouter::getInstance().heap(), static_cast<size_type>(data_len) + 1));
		strcpy_s(ans, data_len + 1, a_data);
		return ans;
	}

	char* hkStringPtr::strNdup(const char* a_data, size_type len)
	{
		auto data_len = std::min(std::strlen(a_data), static_cast<size_t>(len));
		auto ans = static_cast<char*>(hkMemoryRouter::easyAlloc(hkMemoryRouter::getInstance().heap(), static_cast<size_type>(data_len) + 1));
		strncpy_s(ans, data_len + 1, a_data, data_len);
		ans[data_len] = 0;
		return ans;
	}

	const char* hkStringPtr::data() const noexcept
	{
		return reinterpret_cast<const char*>(reinterpret_cast<std::uintptr_t>(_data) & ~kManaged);
	}

	const char* hkStringPtr::c_str() const noexcept
	{
		return data();
	}

	bool hkStringPtr::empty() const noexcept
	{
		return !_data || _data[0] == '\0';
	}

	auto hkStringPtr::size() const
		-> size_type
	{
		return static_cast<size_type>(std::strlen(data()));
	}

	auto hkStringPtr::length() const
		-> size_type
	{
		return size();
	}

	bool operator==(const hkStringPtr& lhs, const hkStringPtr& rhs)
	{
		auto lhs_data = lhs.data();
		auto rhs_data = rhs.data();
		if (!lhs_data)
			return !rhs_data;

		return !std::strcmp(lhs_data, rhs_data);
	}
}
