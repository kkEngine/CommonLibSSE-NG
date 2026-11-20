#include "REL/ID.h"

#include "REX/W32/KERNEL32.h"


namespace REL
{
	namespace detail
	{
		bool memory_map::open(stl::zwstring a_name, std::size_t a_size)
		{
			close();

			REX::W32::ULARGE_INTEGER bytes;
			bytes.value = a_size;

			_mapping = REX::W32::OpenFileMappingW(
				REX::W32::FILE_MAP_READ | REX::W32::FILE_MAP_WRITE,
				false,
				a_name.data());
			if (!_mapping) {
				close();
				return false;
			}

			_view = REX::W32::MapViewOfFile(
				_mapping,
				REX::W32::FILE_MAP_READ | REX::W32::FILE_MAP_WRITE,
				0,
				0,
				bytes.value);
			if (!_view) {
				close();
				return false;
			}

			return true;
		}

		bool memory_map::create(stl::zwstring a_name, std::size_t a_size)
		{
			close();

			REX::W32::ULARGE_INTEGER bytes;
			bytes.value = a_size;

			_mapping = REX::W32::OpenFileMappingW(
				REX::W32::FILE_MAP_READ | REX::W32::FILE_MAP_WRITE,
				false,
				a_name.data());
			if (!_mapping) {
				_mapping = REX::W32::CreateFileMappingW(
					REX::W32::INVALID_HANDLE_VALUE,
					nullptr,
					REX::W32::PAGE_READWRITE,
					bytes.hi,
					bytes.lo,
					a_name.data());
				if (!_mapping) {
					return false;
				}
			}

			_view = REX::W32::MapViewOfFile(
				_mapping,
				REX::W32::FILE_MAP_READ | REX::W32::FILE_MAP_WRITE,
				0,
				0,
				bytes.value);
			if (!_view) {
				return false;
			}

			return true;
		}

		void memory_map::close()
		{
			if (_view) {
				REX::W32::UnmapViewOfFile(static_cast<const void*>(_view));
				_view = nullptr;
			}

			if (_mapping) {
				REX::W32::CloseHandle(_mapping);
				_mapping = nullptr;
			}
		}
	}

	IDDatabase IDDatabase::_instance;

	bool IDDatabase::load_file(stl::zwstring a_filename, Version a_version, bool a_failOnError)
	{
		try {
			istream_t in(a_filename.data(), std::ios::in | std::ios::binary);

			std::int32_t format{};
			in.readin(format);
			if (format != 5) {
				return stl::report_and_error(
					std::format(
						"Unsupported address library format: {}\n"
						"This means this script extender plugin is incompatible with the address "
						"library available for this version of the game, and thus does not "
						"support it."sv,
						format),
					a_failOnError);
			}

			header_t header;
			header.read(in);
			if (header.version() != a_version) {
				return stl::report_and_error("version mismatch"sv, a_failOnError);
			}

			// The file is a dense array (index = id, value = offset, 0 = no entry).
			// Repack it into a sorted sparse table, so lookups and Offset2ID can binary search it.
			std::vector<std::uint32_t> dense(header.offset_count());
			in.readin_n(dense.data(), dense.size());

			std::size_t count = 0;
			for (const auto offset : dense) {
				count += offset != 0;
			}

			auto mapname = L"CommonLibSSEOffsets-v5-"s;
			mapname += a_version.wstring();
			const auto byteSize = count * sizeof(mapping_t);
			if (_mmap.open(mapname, byteSize)) {
				_id2offset = { static_cast<mapping_t*>(_mmap.data()), count };
			} else if (_mmap.create(mapname, byteSize)) {
				_id2offset = { static_cast<mapping_t*>(_mmap.data()), count };
				std::size_t i = 0;
				for (std::size_t id = 0; id < dense.size(); ++id) {
					if (dense[id] != 0) {
						_id2offset[i++] = { id, dense[id] };
					}
				}
			} else {
				return stl::report_and_error("failed to create shared mapping"sv, a_failOnError);
			}
		} catch (const std::system_error&) {
			return stl::report_and_error(
				std::format(
					"Failed to locate an appropriate address library with the path: {}\n"
					"This means you are missing the address library for this specific version of "
					"the game. Please continue to the mod page for address library to download "
					"an appropriate version. If one is not available, then it is likely that "
					"address library has not yet added support for this version of the game."sv,
					stl::utf16_to_utf8(a_filename).value_or("<unknown filename>"s)),
				a_failOnError);
		}

		return true;
	}
}
