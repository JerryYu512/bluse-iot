// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: module_hw.proto

#include "module_hw.pb.h"

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
PROTOBUF_CONSTEXPR BiotAppHardware::BiotAppHardware(
    ::_pbi::ConstantInitialized) {}
struct BiotAppHardwareDefaultTypeInternal {
  PROTOBUF_CONSTEXPR BiotAppHardwareDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~BiotAppHardwareDefaultTypeInternal() {}
  union {
    BiotAppHardware _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 BiotAppHardwareDefaultTypeInternal _BiotAppHardware_default_instance_;
}  // namespace biot
static ::_pb::Metadata file_level_metadata_module_5fhw_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_module_5fhw_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_module_5fhw_2eproto = nullptr;

const uint32_t TableStruct_module_5fhw_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::biot::BiotAppHardware, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::biot::BiotAppHardware)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::biot::_BiotAppHardware_default_instance_._instance,
};

const char descriptor_table_protodef_module_5fhw_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\017module_hw.proto\022\004biot\032\020enums/e_hw.prot"
  "o\"\021\n\017BiotAppHardwareb\006proto3"
  ;
static const ::_pbi::DescriptorTable* const descriptor_table_module_5fhw_2eproto_deps[1] = {
  &::descriptor_table_enums_2fe_5fhw_2eproto,
};
static ::_pbi::once_flag descriptor_table_module_5fhw_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_module_5fhw_2eproto = {
    false, false, 68, descriptor_table_protodef_module_5fhw_2eproto,
    "module_hw.proto",
    &descriptor_table_module_5fhw_2eproto_once, descriptor_table_module_5fhw_2eproto_deps, 1, 1,
    schemas, file_default_instances, TableStruct_module_5fhw_2eproto::offsets,
    file_level_metadata_module_5fhw_2eproto, file_level_enum_descriptors_module_5fhw_2eproto,
    file_level_service_descriptors_module_5fhw_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_module_5fhw_2eproto_getter() {
  return &descriptor_table_module_5fhw_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_module_5fhw_2eproto(&descriptor_table_module_5fhw_2eproto);
namespace biot {

// ===================================================================

class BiotAppHardware::_Internal {
 public:
};

BiotAppHardware::BiotAppHardware(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase(arena, is_message_owned) {
  // @@protoc_insertion_point(arena_constructor:biot.BiotAppHardware)
}
BiotAppHardware::BiotAppHardware(const BiotAppHardware& from)
  : ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:biot.BiotAppHardware)
}





const ::PROTOBUF_NAMESPACE_ID::Message::ClassData BiotAppHardware::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase::CopyImpl,
    ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase::MergeImpl,
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*BiotAppHardware::GetClassData() const { return &_class_data_; }







::PROTOBUF_NAMESPACE_ID::Metadata BiotAppHardware::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_module_5fhw_2eproto_getter, &descriptor_table_module_5fhw_2eproto_once,
      file_level_metadata_module_5fhw_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace biot
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::biot::BiotAppHardware*
Arena::CreateMaybeMessage< ::biot::BiotAppHardware >(Arena* arena) {
  return Arena::CreateMessageInternal< ::biot::BiotAppHardware >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>