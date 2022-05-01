// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: param_module.proto

#include "param_module.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

namespace biot {
PROTOBUF_CONSTEXPR BiotAppModule::BiotAppModule(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.network_)*/nullptr
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct BiotAppModuleDefaultTypeInternal {
  PROTOBUF_CONSTEXPR BiotAppModuleDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~BiotAppModuleDefaultTypeInternal() {}
  union {
    BiotAppModule _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 BiotAppModuleDefaultTypeInternal _BiotAppModule_default_instance_;
}  // namespace biot
static ::_pb::Metadata file_level_metadata_param_5fmodule_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_param_5fmodule_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_param_5fmodule_2eproto = nullptr;

const uint32_t TableStruct_param_5fmodule_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::biot::BiotAppModule, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::biot::BiotAppModule, _impl_.network_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::biot::BiotAppModule)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::biot::_BiotAppModule_default_instance_._instance,
};

const char descriptor_table_protodef_param_5fmodule_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\022param_module.proto\022\004biot\032\016mnetwork.pro"
  "to\"6\n\rBiotAppModule\022%\n\007network\030\001 \001(\0132\024.b"
  "iot.BiotAppNetworkb\006proto3"
  ;
static const ::_pbi::DescriptorTable* const descriptor_table_param_5fmodule_2eproto_deps[1] = {
  &::descriptor_table_mnetwork_2eproto,
};
static ::_pbi::once_flag descriptor_table_param_5fmodule_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_param_5fmodule_2eproto = {
    false, false, 106, descriptor_table_protodef_param_5fmodule_2eproto,
    "param_module.proto",
    &descriptor_table_param_5fmodule_2eproto_once, descriptor_table_param_5fmodule_2eproto_deps, 1, 1,
    schemas, file_default_instances, TableStruct_param_5fmodule_2eproto::offsets,
    file_level_metadata_param_5fmodule_2eproto, file_level_enum_descriptors_param_5fmodule_2eproto,
    file_level_service_descriptors_param_5fmodule_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_param_5fmodule_2eproto_getter() {
  return &descriptor_table_param_5fmodule_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_param_5fmodule_2eproto(&descriptor_table_param_5fmodule_2eproto);
namespace biot {

// ===================================================================

class BiotAppModule::_Internal {
 public:
  static const ::biot::BiotAppNetwork& network(const BiotAppModule* msg);
};

const ::biot::BiotAppNetwork&
BiotAppModule::_Internal::network(const BiotAppModule* msg) {
  return *msg->_impl_.network_;
}
void BiotAppModule::clear_network() {
  if (GetArenaForAllocation() == nullptr && _impl_.network_ != nullptr) {
    delete _impl_.network_;
  }
  _impl_.network_ = nullptr;
}
BiotAppModule::BiotAppModule(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:biot.BiotAppModule)
}
BiotAppModule::BiotAppModule(const BiotAppModule& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  new (&_impl_) Impl_{
      decltype(_impl_.network_){nullptr}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  if (from._internal_has_network()) {
    _impl_.network_ = new ::biot::BiotAppNetwork(*from._impl_.network_);
  }
  // @@protoc_insertion_point(copy_constructor:biot.BiotAppModule)
}

inline void BiotAppModule::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.network_){nullptr}
    , /*decltype(_impl_._cached_size_)*/{}
  };
}

BiotAppModule::~BiotAppModule() {
  // @@protoc_insertion_point(destructor:biot.BiotAppModule)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void BiotAppModule::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  if (this != internal_default_instance()) delete _impl_.network_;
}

void BiotAppModule::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void BiotAppModule::Clear() {
// @@protoc_insertion_point(message_clear_start:biot.BiotAppModule)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  if (GetArenaForAllocation() == nullptr && _impl_.network_ != nullptr) {
    delete _impl_.network_;
  }
  _impl_.network_ = nullptr;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* BiotAppModule::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // .biot.BiotAppNetwork network = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          ptr = ctx->ParseMessage(_internal_mutable_network(), ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* BiotAppModule::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:biot.BiotAppModule)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // .biot.BiotAppNetwork network = 1;
  if (this->_internal_has_network()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(1, _Internal::network(this),
        _Internal::network(this).GetCachedSize(), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:biot.BiotAppModule)
  return target;
}

size_t BiotAppModule::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:biot.BiotAppModule)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // .biot.BiotAppNetwork network = 1;
  if (this->_internal_has_network()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *_impl_.network_);
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData BiotAppModule::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    BiotAppModule::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*BiotAppModule::GetClassData() const { return &_class_data_; }

void BiotAppModule::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<BiotAppModule *>(to)->MergeFrom(
      static_cast<const BiotAppModule &>(from));
}


void BiotAppModule::MergeFrom(const BiotAppModule& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:biot.BiotAppModule)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_has_network()) {
    _internal_mutable_network()->::biot::BiotAppNetwork::MergeFrom(from._internal_network());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void BiotAppModule::CopyFrom(const BiotAppModule& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:biot.BiotAppModule)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool BiotAppModule::IsInitialized() const {
  return true;
}

void BiotAppModule::InternalSwap(BiotAppModule* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_.network_, other->_impl_.network_);
}

::PROTOBUF_NAMESPACE_ID::Metadata BiotAppModule::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_param_5fmodule_2eproto_getter, &descriptor_table_param_5fmodule_2eproto_once,
      file_level_metadata_param_5fmodule_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace biot
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::biot::BiotAppModule*
Arena::CreateMaybeMessage< ::biot::BiotAppModule >(Arena* arena) {
  return Arena::CreateMessageInternal< ::biot::BiotAppModule >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
