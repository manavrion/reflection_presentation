#pragma once

#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/message.h>
#include <google/protobuf/message_lite.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/wire_format.h>

#include <exception>
#include <experimental/compiler>
#include <experimental/meta>
#include <string_view>

#if defined(__clang__)
#define PROTOBUF_FIELD_OFFSET(TYPE, FIELD)                          \
  _Pragma("clang diagnostic push")                                  \
      _Pragma(                                                      \
          "clang diagnostic ignored "                               \
          "\"-Winvalid-offsetof\"") __builtin_offsetof(TYPE, FIELD) \
          _Pragma("clang diagnostic pop")
#else
// Note that we calculate relative to the pointer value 16 here since if we
// just use zero, GCC complains about dereferencing a NULL pointer.  We
// choose 16 rather than some other number just in case the compiler would
// be confused by an unaligned pointer.
#define PROTOBUF_FIELD_OFFSET(TYPE, FIELD)             \
  static_cast< ::google::protobuf::uint32>(            \
      reinterpret_cast<const char*>(                   \
          &reinterpret_cast<const TYPE*>(16)->FIELD) - \
      reinterpret_cast<const char*>(16))
#endif

namespace magic_proto {

namespace meta = std::experimental::meta;
namespace protobuf = ::google::protobuf;

consteval std::string_view operator+(const std::string_view lhs,
                                     const std::string_view rhs) {
  return __concatenate(lhs.data(), rhs.data());
}

struct proto_info {
  std::string_view name;
  size_t index;
};

template <class T, class Operator>
void for_each_by_proto_info(Operator&& op) {
  consteval {
    auto info = reflexpr(std::decay_t<T>);
    auto range = meta::data_member_range(info);
    for (auto it = range.begin(); it != range.end(); ++it) {
      if (std::string_view{meta::name_of(meta::type_of(*it))} ==
          "const magic_proto::proto_info") {
        auto proto_details_info = *it;
        ->__fragment{{auto proto_details =
                          unqualid(meta::name_of(meta::definition_of(info)),
                                   "::", meta::name_of(proto_details_info));
        op(proto_details);
      }
    };
  }
}
}  // namespace magic_proto
}

template <typename T, typename U>
constexpr size_t offsetOf(U T::*member) {
  return (char*)&((T*)nullptr->*member) - (char*)nullptr;
}

template <class T>
void for_each_by_member_pointers_special(
    std::vector<protobuf::uint32>& offsets) {
  consteval {
    auto info = reflexpr(T);
    auto range = meta::data_member_range(info);
    for (auto it = range.begin(); it != range.end(); ++it) {
      if (std::string_view{meta::name_of(meta::type_of(*it))} ==
          "const magic_proto::proto_info") {
        auto proto_details_info = *it;
        while (!meta::is_nonstatic_data_member_fn{}(*it)) {
          ++it;
        }
        ->__fragment{{auto ptr = valueof(*it);
        offsets.push_back(offsetOf(ptr));
      }
    };
  }
}
}
}

template <class T, class Operator>
void for_each_by_proto_members(T&& t, Operator&& op) {
  consteval {
    auto info = reflexpr(std::decay_t<T>);
    auto range = meta::data_member_range(info);
    for (auto it = range.begin(); it != range.end(); ++it) {
      if (std::string_view{meta::name_of(meta::type_of(*it))} ==
          "const magic_proto::proto_info") {
        auto proto_details_info = *it;
        while (!meta::is_nonstatic_data_member_fn{}(*it)) {
          ++it;
        }
        ->__fragment{{auto ptr = valueof(*it);
        auto proto_details = unqualid(meta::name_of(meta::definition_of(info)),
                                      "::", meta::name_of(proto_details_info));
        op(std::forward<T>(t).*ptr, proto_details);
      }
    };
  }
}
}
}

template <class T1, class T2, class Operator>
void double_for_each_by_proto_members(T1&& t1, T2&& t2, Operator&& op) {
  consteval {
    auto info = reflexpr(std::decay_t<T1>);
    auto range = meta::data_member_range(info);
    for (auto it = range.begin(); it != range.end(); ++it) {
      if (std::string_view{meta::name_of(meta::type_of(*it))} ==
          "const magic_proto::proto_info") {
        auto proto_details_info = *it;
        while (!meta::is_nonstatic_data_member_fn{}(*it)) {
          ++it;
        }
        ->__fragment{{auto ptr = valueof(*it);
        auto proto_details = unqualid(meta::name_of(meta::definition_of(info)),
                                      "::", meta::name_of(proto_details_info));
        op(std::forward<T1>(t1).*ptr, std::forward<T2>(t2).*ptr, proto_details);
      }
    };
  }
}
}
}

consteval void inject_proto_details_for_member(meta::info that,
                                               meta::info member,
                                               const size_t index) {
  std::string_view name = meta::name_of(member);
  std::string_view field_name = __concatenate(name.data(), "_");
  std::string_view set_name = __concatenate("set_", name.data());
  std::string_view get_name = name.data();

  meta::info type = meta::type_of(member);

  meta::set_new_name(member, field_name.data());
  meta::make_private(member);

  ->__fragment struct T {
    const static proto_info unqualid("index_", name.data());
  };

  ->namespace __fragment namespace {
    inline const proto_info unqualid(meta::name_of(that), "::index_",
                                     name.data()) = {name, index};
  };

  ->member;

  ->__fragment struct {
    void unqualid(set_name.data())(const typename(type) &
                                   unqualid(field_name.data())) {
      this->unqualid(field_name.data()) = unqualid(field_name.data());
    }
  };

  ->__fragment struct {
    const typename(type) & unqualid(get_name.data())() const {
      return unqualid(field_name.data());
    }
  };
}

consteval void proto_message(meta::info info) {
  ->__fragment struct T : public protobuf::Message {
    consteval {
      __inject_base(public protobuf::Message);

      size_t index = 0;
      for (meta::info member : meta::member_range(info)) {
        inject_proto_details_for_member(reflexpr(T), member, ++index);
      }
    }

    // Fields
    protobuf::internal::InternalMetadataWithArena _internal_metadata_;
    mutable protobuf::internal::CachedSize _cached_size_;

    T() : protobuf::Message(), _internal_metadata_(nullptr) { Clear(); }

    virtual ~T() noexcept {}

    T(const T& from) : _internal_metadata_(nullptr) {
      _internal_metadata_.MergeFrom(from._internal_metadata_);
      CopyFrom(from);
    }

    T(T&& from) noexcept : T() { *this = ::std::move(from); }

    T& operator=(const T& from) {
      CopyFrom(from);
      return *this;
    }

    T& operator=(T&& from) noexcept {
      if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
        if (this != &from) InternalSwap(&from);
      } else {
        CopyFrom(from);
      }
      return *this;
    }

    T* New() const final {
      return new T();  // TODO: arena support
    }

    void Clear() final {
      for_each_by_proto_members(*this,
                                [](auto& member, auto info) { member = {}; });
    }

    bool IsInitialized() const final { return true; }

    void SetCachedSize(int size) const final { _cached_size_.Set(size); }

    size_t ByteSizeLong() const final {
      throw std::runtime_error("ByteSizeLong called");
      size_t total_size = 0;
      if (_internal_metadata_.have_unknown_fields()) {
        total_size += protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
            _internal_metadata_.unknown_fields());
      }

      for_each_by_proto_members(*this, [&total_size](auto& member, auto info) {
        total_size += 1 + protobuf::internal::WireFormatLite::Int64Size(member);
      });

      int cached_size = protobuf::internal::ToCachedSize(total_size);
      SetCachedSize(cached_size);
      return total_size;
    }

    int GetCachedSize() const final { return _cached_size_.Get(); }

    void InternalSwap(T* other) {
      // TODO
      throw std::runtime_error("InternalSwap");
    }

    void CopyFrom(const T& from) {
      if (&from == this) return;
      Clear();
      MergeFrom(from);
    }

    void MergeFrom(const T& from) {
      _internal_metadata_.MergeFrom(from._internal_metadata_);
      double_for_each_by_proto_members(
          *this, from, [](auto& this_member, auto& from_member, auto info) {
            this_member = from_member;
          });
    }

    protobuf::Arena* GetArenaNoVirtual() const { return nullptr; }

    protobuf::uint8* _InternalSerialize(
        protobuf::uint8* ptr,
        protobuf::io::EpsCopyOutputStream* stream) const final {
      throw std::runtime_error("_InternalSerialize called");
      return {};
    }

    static void InitDefaultsscc_info() {
      static class DefaultTypeInternal {
       public:
        protobuf::internal::ExplicitlyConstructed<T> _instance;
      } _default_instance_;
      {
        void* ptr = &_default_instance_;
        new (ptr) T();
        protobuf::internal::OnShutdownDestroyMessage(ptr);
      }
      //::proto_experiments::SimpleMessage0::InitAsDefaultInstance();
    }

    protobuf::Metadata GetMetadataNoStatic() const {
      static bool is_initialized = false;

      static class DefaultTypeInternal {
       public:
        protobuf::internal::ExplicitlyConstructed<T> _instance;
      } _default_instance_;

      // Metadata
      constexpr std::string_view message_name =
          meta::name_of(meta::definition_of(info));

      constexpr std::string_view file_name = message_name + ".proto";
      constexpr std::string_view package = "cpp_generated";

      static std::string static_descriptor_table;
      if (static_descriptor_table.empty()) {
        protobuf::FileDescriptorProto file_proto;

        file_proto.set_syntax("proto3");
        file_proto.set_name(file_name.data());
        file_proto.set_package(package.data());
        auto& message_descriptor = *file_proto.add_message_type();

        message_descriptor.set_name(message_name.data());
        for_each_by_proto_info<T>([&message_descriptor](auto info) {
          auto& field_descriptor = *message_descriptor.add_field();
          field_descriptor.set_name(info.name.data());
          field_descriptor.set_number(info.index);
          field_descriptor.set_type(protobuf::FieldDescriptorProto::TYPE_INT64);
          field_descriptor.set_label(
              protobuf::FieldDescriptorProto::LABEL_OPTIONAL);
        });

        file_proto.SerializeToString(&static_descriptor_table);
      }

      static protobuf::internal::once_flag once_flag;

      static protobuf::internal::SCCInfo<0> scc_info = {
          {ATOMIC_VAR_INIT(protobuf::internal::SCCInfoBase::kUninitialized), 0,
           0, InitDefaultsscc_info},
          {}};

      static protobuf::internal::SCCInfoBase* const init_default_instances[] = {
          &scc_info.base,
      };

      static const protobuf::internal::DescriptorTable* const
          descriptor_table_deps[1] = {};

      static const protobuf::internal::MigrationSchema schemas[] = {
          {0, -1, sizeof(T)},
      };

      static protobuf::Message const* const file_default_instances[] = {
          reinterpret_cast<const protobuf::Message*>(&_default_instance_),
      };

      static std::vector<protobuf::uint32> offsets;

      if (offsets.empty()) {
        offsets.emplace_back(~0u),  // no _has_bits_);
        offsets.emplace_back(offsetOf(&T::_internal_metadata_));
        offsets.emplace_back(~0u);  // no _extensions_
        offsets.emplace_back(~0u);  // no _oneof_case_
        offsets.emplace_back(~0u);  // no _weak_field_map_
        // TODO
        // PROTOBUF_FIELD_OFFSET(T, member_pointer)
        // std::cout << "DEBUG offsets: " << offsets.size() << std::endl;
        for_each_by_member_pointers_special<T>(offsets);
        // std::cout << "DEBUG offsets: " << offsets.size() << std::endl;
        // for (auto o : offsets) {
        //  std::cout << o << " ";
        //}
        // std::cout << std::endl;
      }

      static protobuf::Metadata file_level_metadata;

      static constexpr protobuf::EnumDescriptor const**
          file_level_enum_descriptors = nullptr;
      static constexpr protobuf::ServiceDescriptor const**
          file_level_service_descriptors = nullptr;

      static const protobuf::internal::DescriptorTable descriptor_table = {
          .is_initialized = &is_initialized,
          .descriptor = static_descriptor_table.c_str(),
          .filename = file_name.data(),
          .size = static_cast<int>(static_descriptor_table.size()),
          .once = &once_flag,
          .init_default_instances = init_default_instances,
          .deps = descriptor_table_deps,
          .num_sccs = 1,
          .num_deps = 0,
          .schemas = schemas,
          .default_instances = file_default_instances,
          .offsets = offsets.data(),
          .file_level_metadata = &file_level_metadata,
          .num_messages = 1,
          .file_level_enum_descriptors = file_level_enum_descriptors,
          .file_level_service_descriptors = file_level_service_descriptors,
      };

#if 0
      static bool dynamic_init_dummy_sample_2eproto =
          (static_cast<void>(
               protobuf::internal::AddDescriptors(&descriptor_table)),
           true);
#endif

      static constexpr int kIndexInFileMessages = 0;

      // Original method
      protobuf::internal::AssignDescriptors(&descriptor_table);

      if (file_level_metadata.descriptor == nullptr ||
          file_level_metadata.reflection == nullptr) {
        throw std::runtime_error("bad file_level_metadata");
      }

      return file_level_metadata;
    }

    const protobuf::Descriptor* descriptor() {
      throw std::runtime_error("descriptor called");
      return GetDescriptor();
    }
    const protobuf::Descriptor* GetDescriptor() {
      throw std::runtime_error("GetDescriptor called");
      return GetMetadataNoStatic().descriptor;
    }
    const protobuf::Reflection* GetReflection() {
      throw std::runtime_error("GetReflection called");
      return GetMetadataNoStatic().reflection;
    }

    protobuf::Metadata GetMetadata() const final {
      // throw std::runtime_error("GetMetadata called");
      return GetMetadataNoStatic();
    }

    // std::string DebugStringG() const {
    //  return DebugString();
    //}
  };
}
}
