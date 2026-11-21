#pragma once

#include "REL/Module.h"

namespace REL
{
    namespace detail
    {
        class memory_map
        {
        public:
            memory_map() noexcept = default;
            memory_map(const memory_map&) = delete;

            memory_map(memory_map&& a_rhs) noexcept:
                _mapping(a_rhs._mapping),
                _view(a_rhs._view)
            {
                a_rhs._mapping = nullptr;
                a_rhs._view = nullptr;
            }

            ~memory_map() { close(); }

            memory_map &operator=(const memory_map&) = delete;

            memory_map &operator=(memory_map&& a_rhs) noexcept
            {
                if (this != std::addressof(a_rhs)) {
                    _mapping = a_rhs._mapping;
                    a_rhs._mapping = nullptr;

                    _view = a_rhs._view;
                    a_rhs._view = nullptr;
                }

                return *this;
            }

            [[nodiscard]] void* data() noexcept { return _view; }

            bool open(stl::zwstring a_name, std::size_t a_size);

            bool create(stl::zwstring a_name, std::size_t a_size);

            void close();

        private:
            void* _mapping{nullptr};
            void* _view{nullptr};
        };
    }

    class IDDatabase
    {
    private:
        struct mapping_t
        {
            std::uint64_t id;
            std::uint64_t offset;
        };

    public:
        enum class Format
        {
            SSEv1,
            SSEv2,
            VR,
            SSEv5  // AE 1.7.99+: dense uint32 array indexed by id
        };

        class Offset2ID
        {
        public:
            using value_type = mapping_t;
            using container_type = std::vector<value_type>;
            using size_type = typename container_type::size_type;
            using const_iterator = typename container_type::const_iterator;
            using const_reverse_iterator = typename container_type::const_reverse_iterator;

            template<class ExecutionPolicy>
            explicit Offset2ID(ExecutionPolicy&& a_policy)
            requires(std::is_execution_policy_v<std::decay_t<ExecutionPolicy>>)
            {
                const std::span<const mapping_t> id2offset = IDDatabase::get()._id2offset;
                _offset2id.reserve(id2offset.size());
                _offset2id.insert(_offset2id.begin(), id2offset.begin(), id2offset.end());
                std::sort(a_policy, _offset2id.begin(), _offset2id.end(), [](auto &&a_lhs, auto &&a_rhs) {
                        return a_lhs.offset < a_rhs.offset;
                });
            }

            Offset2ID() :
                Offset2ID(std::execution::sequenced_policy{})
            {}

            [[nodiscard]] std::uint64_t operator()(std::size_t a_offset) const
            {
                const mapping_t elem{0, a_offset};
                const auto it = std::lower_bound(
                        _offset2id.begin(),
                        _offset2id.end(),
                        elem,
                        [](auto &&a_lhs, auto &&a_rhs) {
                            return a_lhs.offset < a_rhs.offset;
                        });
                if (it == _offset2id.end()) {
                    stl::report_and_fail(
                            std::format(
                                    "Failed to find the offset within the database: 0x{:08X}"sv,
                                    a_offset));
                }

                return it->id;
            }

            [[nodiscard]] const_iterator begin() const noexcept { return _offset2id.begin(); }
            [[nodiscard]] const_iterator cbegin() const noexcept { return _offset2id.cbegin(); }
            [[nodiscard]] const_iterator end() const noexcept { return _offset2id.end(); }
            [[nodiscard]] const_iterator cend() const noexcept { return _offset2id.cend(); }
            [[nodiscard]] const_reverse_iterator rbegin() const noexcept { return _offset2id.rbegin(); }
            [[nodiscard]] const_reverse_iterator crbegin() const noexcept { return _offset2id.crbegin(); }
            [[nodiscard]] const_reverse_iterator rend() const noexcept { return _offset2id.rend(); }
            [[nodiscard]] const_reverse_iterator crend() const noexcept { return _offset2id.crend(); }
            [[nodiscard]] size_type size() const noexcept { return _offset2id.size(); }

        private:
            container_type _offset2id;
        };

        [[nodiscard]] static IDDatabase& get()
        {
            if (_initialized.load(std::memory_order_relaxed)) {
                return _instance;
            }
            [[maybe_unused]] std::unique_lock lock(_initLock);
            _instance.load();
            _initialized.store(true, std::memory_order_relaxed);
            return _instance;
        }

#ifdef ENABLE_COMMONLIBSSE_TESTING
        [[nodiscard]] static bool inject(std::wstring_view a_filePath, Format a_format)
        {
            return inject(a_filePath, a_format, Module::get().version());
        }

        [[nodiscard]] static bool inject(std::wstring_view a_filePath, Format a_format, Version a_version)
        {
            _initialized = true;
            _instance.clear();
            switch (a_format) {
                case Format::SSEv1:
                    return _instance.load_file(a_filePath.data(), a_version, 1, false);
                case Format::SSEv2:
                    return _instance.load_file(a_filePath.data(), a_version, 2, false);
                case Format::SSEv5:
                    return _instance.load_file(a_filePath.data(), a_version, 5, false);
                default:
                    return false;
            }
        }

        static void reset()
        {
            _instance.clear();
            _initialized = false;
        }
#endif

        [[nodiscard]] inline std::size_t id2offset(std::uint64_t a_id) const
        {
            mapping_t elem{a_id, 0};
            const auto it = std::lower_bound(
                    _id2offset.begin(),
                    _id2offset.end(),
                    elem,
                    [](auto &&a_lhs, auto &&a_rhs) {
                        return a_lhs.id < a_rhs.id;
                    });

            // An id missing from the library must not silently resolve to its neighbour:
            // AE 1.7.99 retired many ids, so a stale id would otherwise patch random code.
            const bool failed = it == _id2offset.end() || it->id != a_id;
            if (failed) {
                stl::report_and_fail(
                    std::format(
                        "Failed to find the id within the address library: {}\n"
                        "This means this script extender plugin is incompatible with the address "
                        "library for this version of the game, and thus does not support it."sv,
                        a_id));
            }

            return static_cast<std::size_t>(it->offset);
        }

    private:
        friend class Module;

        class istream_t
        {
        public:
            using stream_type = std::ifstream;
            using pointer = stream_type *;
            using const_pointer = const stream_type *;
            using reference = stream_type &;
            using const_reference = const stream_type &;

            inline istream_t(stl::zwstring a_filename, std::ios_base::openmode a_mode) :
                _stream(a_filename.data(), a_mode)
            {
                if (!_stream.is_open()) {
                    stl::report_and_fail("failed to open address library file");
                }

                _stream.exceptions(std::ios::badbit | std::ios::failbit | std::ios::eofbit);
            }

            inline void ignore(std::streamsize a_count) { _stream.ignore(a_count); }

            template<class T>
            inline void readin(T &a_val)
            {
                _stream.read(reinterpret_cast<char *>(std::addressof(a_val)), sizeof(T));
            }

            template<class T>
            inline void readin_n(T *a_vals, std::size_t a_count)
            {
                _stream.read(reinterpret_cast<char *>(a_vals), static_cast<std::streamsize>(a_count * sizeof(T)));
            }

            template<
                    class T,
                    std::enable_if_t<
                            std::is_arithmetic_v<T>,
                            int> = 0>
            inline T readout()
            {
                T val{};
                readin(val);
                return val;
            }

        private:
            stream_type _stream;
        };

        class header_t
        {
        public:
            void read(istream_t &a_in, std::uint8_t a_formatVersion)
            {
                std::int32_t format{};
                a_in.readin(format);
                if (format != a_formatVersion) {
                    stl::report_and_fail(
                            std::format(
                                    "Unsupported address library format: {}\n"
                                    "This means this script extender plugin is incompatible with the address "
                                    "library available for this version of the game, and thus does not "
                                    "support it."sv,
                                    format));
                }

                std::int32_t version[4]{};
                std::int32_t nameLen{};
                a_in.readin(version);
                a_in.readin(nameLen);
                a_in.ignore(nameLen);

                a_in.readin(_pointerSize);
                a_in.readin(_addressCount);

                for (std::size_t i = 0; i < std::extent_v<decltype(version)>; ++i) {
                    _version[i] = static_cast<std::uint16_t>(version[i]);
                }
            }

            [[nodiscard]] std::size_t address_count() const noexcept { return static_cast<std::size_t>(_addressCount); }

            [[nodiscard]] std::uint64_t pointer_size() const noexcept { return static_cast<std::uint64_t>(_pointerSize); }

            [[nodiscard]] Version version() const noexcept { return _version; }

        private:
            Version      _version;
            std::int32_t _pointerSize{0};
            std::int32_t _addressCount{0};
        };

        // Header of format 5 (AE 1.7.99+): fixed 64-byte name, pointer size,
        // reserved data format and the element count of the dense offset array.
        class header_v5_t
        {
        public:
            void read(istream_t &a_in)
            {
                std::uint32_t version[4]{};
                char          name[64]{};
                a_in.readin(version);
                a_in.readin(name);
                a_in.readin(_pointerSize);
                a_in.readin(_dataFormat);
                a_in.readin(_offsetCount);

                for (std::size_t i = 0; i < std::extent_v<decltype(version)>; ++i) {
                    _version[i] = static_cast<std::uint16_t>(version[i]);
                }
            }

            [[nodiscard]] std::size_t offset_count() const noexcept { return static_cast<std::size_t>(_offsetCount); }

            [[nodiscard]] Version version() const noexcept { return _version; }

        private:
            Version      _version;
            std::int32_t _pointerSize{0};
            std::int32_t _dataFormat{0};
            std::int32_t _offsetCount{0};
        };

        IDDatabase() = default;
        IDDatabase(const IDDatabase&) = delete;
        IDDatabase(IDDatabase&&) = delete;

        ~IDDatabase() = default;

        IDDatabase& operator=(const IDDatabase&) = delete;
        IDDatabase& operator=(IDDatabase&&) = delete;

        void load()
        {
            const auto version = Module::get().version();
                const auto filename =
                        stl::utf8_to_utf16(
                            Module::IsAE() ?
                                std::format("Data/SKSE/Plugins/versionlib-{}.bin"sv, version.string()) :
                                std::format("Data/SKSE/Plugins/version-{}.bin"sv, version.string()))
                                .value_or(L"<unknown filename>"s);
                // AE 1.7.99+ ships format 5, older AE format 2, SE format 1.
                load_file(filename, version, Module::IsAE() ? (version >= Version(1, 7, 99, 0) ? 5 : 2) : 1, true);
        }

        bool load_file(stl::zwstring a_filename, Version a_version, std::uint8_t a_formatVersion, bool a_failOnError);

        bool load_v5(istream_t &a_in, Version a_version, bool a_failOnError);


        bool unpack_file(istream_t &a_in, header_t a_header, bool a_failOnError)
        {
            std::uint8_t type = 0;
            std::uint64_t id = 0;
            std::uint64_t offset = 0;
            std::uint64_t prevID = 0;
            std::uint64_t prevOffset = 0;
            for (auto& mapping: _id2offset) {
                a_in.readin(type);
                const auto lo = static_cast<std::uint8_t>(type & 0xF);
                const auto hi = static_cast<std::uint8_t>(type >> 4);

                switch (lo) {
                    case 0:
                        a_in.readin(id);
                        break;
                    case 1:
                        id = prevID + 1;
                        break;
                    case 2:
                        id = prevID + a_in.readout<std::uint8_t>();
                        break;
                    case 3:
                        id = prevID - a_in.readout<std::uint8_t>();
                        break;
                    case 4:
                        id = prevID + a_in.readout<std::uint16_t>();
                        break;
                    case 5:
                        id = prevID - a_in.readout<std::uint16_t>();
                        break;
                    case 6:
                        id = a_in.readout<std::uint16_t>();
                        break;
                    case 7:
                        id = a_in.readout<std::uint32_t>();
                        break;
                    default:
                        return stl::report_and_error("unhandled type"sv, a_failOnError);
                }

                const std::uint64_t tmp = (hi & 8) != 0 ? (prevOffset / a_header.pointer_size()) : prevOffset;

                switch (hi & 7) {
                    case 0:
                        a_in.readin(offset);
                        break;
                    case 1:
                        offset = tmp + 1;
                        break;
                    case 2:
                        offset = tmp + a_in.readout<std::uint8_t>();
                        break;
                    case 3:
                        offset = tmp - a_in.readout<std::uint8_t>();
                        break;
                    case 4:
                        offset = tmp + a_in.readout<std::uint16_t>();
                        break;
                    case 5:
                        offset = tmp - a_in.readout<std::uint16_t>();
                        break;
                    case 6:
                        offset = a_in.readout<std::uint16_t>();
                        break;
                    case 7:
                        offset = a_in.readout<std::uint32_t>();
                        break;
                    default:
                        return stl::report_and_error("unhandled type"sv, a_failOnError);
                }

                if ((hi & 8) != 0) {
                    offset *= a_header.pointer_size();
                }

                mapping = {id, offset};

                prevOffset = offset;
                prevID = id;
            }

            return true;
        }

        void clear()
        {
            _mmap.close();
            _id2offset = {};
        }

        static IDDatabase              _instance;
        static inline std::atomic_bool _initialized{false};
        static inline std::mutex       _initLock;
        detail::memory_map             _mmap;
        std::span<mapping_t>           _id2offset;
    };

    class ID
    {
    public:
        constexpr ID() noexcept = default;

        explicit constexpr ID(std::uint64_t a_id) noexcept:
            _id(a_id)
        {}

        constexpr ID &operator=(std::uint64_t a_id) noexcept
        {
            _id = a_id;
            return *this;
        }

        [[nodiscard]] std::uintptr_t address() const { return base() + offset(); }

        [[nodiscard]] constexpr std::uint64_t id() const noexcept { return _id; }

        [[nodiscard]] std::size_t offset() const { return IDDatabase::get().id2offset(_id); }

    private:
        [[nodiscard]] static std::uintptr_t base() { return Module::get().base(); }

        std::uint64_t _id{0};
    };

    class RelocationID
    {
    public:
        constexpr RelocationID() noexcept = default;

        explicit constexpr RelocationID(
            [[maybe_unused]] std::uint64_t a_seID,
            [[maybe_unused]] std::uint64_t a_aeID) noexcept
        {
            _aeID = a_aeID;
        }

        explicit constexpr RelocationID(
            [[maybe_unused]] std::uint64_t a_seID,
            [[maybe_unused]] std::uint64_t a_aeID,
            [[maybe_unused]] std::uint64_t a_vrID) noexcept
        {
            _aeID = a_aeID;
        }

        [[nodiscard]] std::uintptr_t address() const
        {
            auto thisOffset = offset();
            return thisOffset ? base() + offset() : 0;
        }

        [[nodiscard]] std::size_t offset() const
        {
            auto thisID = id();
            return thisID ? IDDatabase::get().id2offset(thisID) : 0;
        }

        [[nodiscard]] constexpr std::uint64_t id() const noexcept
        {
            switch (Module::GetRuntime()) {
                case Module::Runtime::AE:
                    return _aeID;
                default:
                    return 0;
            }
        }

        [[nodiscard]] constexpr explicit operator ID() const noexcept {
            return ID(id());
        }

    private:
        [[nodiscard]] static std::uintptr_t base() { return Module::get().base(); }

        std::uint64_t _aeID{0};
    };

    class VariantID
    {
    public:
        constexpr VariantID() noexcept = default;

        explicit constexpr VariantID(
            [[maybe_unused]] std::uint64_t a_seID,
            [[maybe_unused]] std::uint64_t a_aeID,
            [[maybe_unused]] std::uint64_t a_vrOffset) noexcept
        {
            _aeID = a_aeID;
        }

        [[nodiscard]] std::uintptr_t address() const
        {
            auto thisOffset = offset();
            return thisOffset ? base() + offset() : 0;
        }

        [[nodiscard]] std::size_t offset() const
        {
            switch (Module::GetRuntime()) {
                case Module::Runtime::AE:
                    return _aeID ? IDDatabase::get().id2offset(_aeID) : 0;
                default:
                    return 0;
            }
        }

    private:
        [[nodiscard]] static std::uintptr_t base() { return Module::get().base(); }

        std::uint64_t _aeID{0};
    };
}
