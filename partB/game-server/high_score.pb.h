// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: high_score.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_high_5fscore_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_high_5fscore_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3012000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3012004 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_high_5fscore_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_high_5fscore_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_high_5fscore_2eproto;
class HighScore;
class HighScoreDefaultTypeInternal;
extern HighScoreDefaultTypeInternal _HighScore_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::HighScore* Arena::CreateMaybeMessage<::HighScore>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

// ===================================================================

class HighScore PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:HighScore) */ {
 public:
  inline HighScore() : HighScore(nullptr) {};
  virtual ~HighScore();

  HighScore(const HighScore& from);
  HighScore(HighScore&& from) noexcept
    : HighScore() {
    *this = ::std::move(from);
  }

  inline HighScore& operator=(const HighScore& from) {
    CopyFrom(from);
    return *this;
  }
  inline HighScore& operator=(HighScore&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const HighScore& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const HighScore* internal_default_instance() {
    return reinterpret_cast<const HighScore*>(
               &_HighScore_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(HighScore& a, HighScore& b) {
    a.Swap(&b);
  }
  inline void Swap(HighScore* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(HighScore* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline HighScore* New() const final {
    return CreateMaybeMessage<HighScore>(nullptr);
  }

  HighScore* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<HighScore>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const HighScore& from);
  void MergeFrom(const HighScore& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(HighScore* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "HighScore";
  }
  protected:
  explicit HighScore(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_high_5fscore_2eproto);
    return ::descriptor_table_high_5fscore_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kPAFieldNumber = 1,
    kPBFieldNumber = 2,
    kPCFieldNumber = 3,
    kPDFieldNumber = 4,
    kPEFieldNumber = 5,
    kPFFieldNumber = 6,
    kPGFieldNumber = 7,
    kPHFieldNumber = 8,
    kGameFieldNumber = 9,
  };
  // optional int32 pA = 1;
  bool has_pa() const;
  private:
  bool _internal_has_pa() const;
  public:
  void clear_pa();
  ::PROTOBUF_NAMESPACE_ID::int32 pa() const;
  void set_pa(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_pa() const;
  void _internal_set_pa(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // optional int32 pB = 2;
  bool has_pb() const;
  private:
  bool _internal_has_pb() const;
  public:
  void clear_pb();
  ::PROTOBUF_NAMESPACE_ID::int32 pb() const;
  void set_pb(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_pb() const;
  void _internal_set_pb(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // optional int32 pC = 3;
  bool has_pc() const;
  private:
  bool _internal_has_pc() const;
  public:
  void clear_pc();
  ::PROTOBUF_NAMESPACE_ID::int32 pc() const;
  void set_pc(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_pc() const;
  void _internal_set_pc(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // optional int32 pD = 4;
  bool has_pd() const;
  private:
  bool _internal_has_pd() const;
  public:
  void clear_pd();
  ::PROTOBUF_NAMESPACE_ID::int32 pd() const;
  void set_pd(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_pd() const;
  void _internal_set_pd(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // optional int32 pE = 5;
  bool has_pe() const;
  private:
  bool _internal_has_pe() const;
  public:
  void clear_pe();
  ::PROTOBUF_NAMESPACE_ID::int32 pe() const;
  void set_pe(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_pe() const;
  void _internal_set_pe(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // optional int32 pF = 6;
  bool has_pf() const;
  private:
  bool _internal_has_pf() const;
  public:
  void clear_pf();
  ::PROTOBUF_NAMESPACE_ID::int32 pf() const;
  void set_pf(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_pf() const;
  void _internal_set_pf(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // optional int32 pG = 7;
  bool has_pg() const;
  private:
  bool _internal_has_pg() const;
  public:
  void clear_pg();
  ::PROTOBUF_NAMESPACE_ID::int32 pg() const;
  void set_pg(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_pg() const;
  void _internal_set_pg(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // optional int32 pH = 8;
  bool has_ph() const;
  private:
  bool _internal_has_ph() const;
  public:
  void clear_ph();
  ::PROTOBUF_NAMESPACE_ID::int32 ph() const;
  void set_ph(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_ph() const;
  void _internal_set_ph(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // optional int32 game = 9;
  bool has_game() const;
  private:
  bool _internal_has_game() const;
  public:
  void clear_game();
  ::PROTOBUF_NAMESPACE_ID::int32 game() const;
  void set_game(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_game() const;
  void _internal_set_game(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // @@protoc_insertion_point(class_scope:HighScore)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::int32 pa_;
  ::PROTOBUF_NAMESPACE_ID::int32 pb_;
  ::PROTOBUF_NAMESPACE_ID::int32 pc_;
  ::PROTOBUF_NAMESPACE_ID::int32 pd_;
  ::PROTOBUF_NAMESPACE_ID::int32 pe_;
  ::PROTOBUF_NAMESPACE_ID::int32 pf_;
  ::PROTOBUF_NAMESPACE_ID::int32 pg_;
  ::PROTOBUF_NAMESPACE_ID::int32 ph_;
  ::PROTOBUF_NAMESPACE_ID::int32 game_;
  friend struct ::TableStruct_high_5fscore_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// HighScore

// optional int32 game = 9;
inline bool HighScore::_internal_has_game() const {
  bool value = (_has_bits_[0] & 0x00000100u) != 0;
  return value;
}
inline bool HighScore::has_game() const {
  return _internal_has_game();
}
inline void HighScore::clear_game() {
  game_ = 0;
  _has_bits_[0] &= ~0x00000100u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 HighScore::_internal_game() const {
  return game_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 HighScore::game() const {
  // @@protoc_insertion_point(field_get:HighScore.game)
  return _internal_game();
}
inline void HighScore::_internal_set_game(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000100u;
  game_ = value;
}
inline void HighScore::set_game(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_game(value);
  // @@protoc_insertion_point(field_set:HighScore.game)
}

// optional int32 pA = 1;
inline bool HighScore::_internal_has_pa() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool HighScore::has_pa() const {
  return _internal_has_pa();
}
inline void HighScore::clear_pa() {
  pa_ = 0;
  _has_bits_[0] &= ~0x00000001u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 HighScore::_internal_pa() const {
  return pa_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 HighScore::pa() const {
  // @@protoc_insertion_point(field_get:HighScore.pA)
  return _internal_pa();
}
inline void HighScore::_internal_set_pa(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000001u;
  pa_ = value;
}
inline void HighScore::set_pa(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_pa(value);
  // @@protoc_insertion_point(field_set:HighScore.pA)
}

// optional int32 pB = 2;
inline bool HighScore::_internal_has_pb() const {
  bool value = (_has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool HighScore::has_pb() const {
  return _internal_has_pb();
}
inline void HighScore::clear_pb() {
  pb_ = 0;
  _has_bits_[0] &= ~0x00000002u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 HighScore::_internal_pb() const {
  return pb_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 HighScore::pb() const {
  // @@protoc_insertion_point(field_get:HighScore.pB)
  return _internal_pb();
}
inline void HighScore::_internal_set_pb(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000002u;
  pb_ = value;
}
inline void HighScore::set_pb(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_pb(value);
  // @@protoc_insertion_point(field_set:HighScore.pB)
}

// optional int32 pC = 3;
inline bool HighScore::_internal_has_pc() const {
  bool value = (_has_bits_[0] & 0x00000004u) != 0;
  return value;
}
inline bool HighScore::has_pc() const {
  return _internal_has_pc();
}
inline void HighScore::clear_pc() {
  pc_ = 0;
  _has_bits_[0] &= ~0x00000004u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 HighScore::_internal_pc() const {
  return pc_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 HighScore::pc() const {
  // @@protoc_insertion_point(field_get:HighScore.pC)
  return _internal_pc();
}
inline void HighScore::_internal_set_pc(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000004u;
  pc_ = value;
}
inline void HighScore::set_pc(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_pc(value);
  // @@protoc_insertion_point(field_set:HighScore.pC)
}

// optional int32 pD = 4;
inline bool HighScore::_internal_has_pd() const {
  bool value = (_has_bits_[0] & 0x00000008u) != 0;
  return value;
}
inline bool HighScore::has_pd() const {
  return _internal_has_pd();
}
inline void HighScore::clear_pd() {
  pd_ = 0;
  _has_bits_[0] &= ~0x00000008u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 HighScore::_internal_pd() const {
  return pd_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 HighScore::pd() const {
  // @@protoc_insertion_point(field_get:HighScore.pD)
  return _internal_pd();
}
inline void HighScore::_internal_set_pd(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000008u;
  pd_ = value;
}
inline void HighScore::set_pd(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_pd(value);
  // @@protoc_insertion_point(field_set:HighScore.pD)
}

// optional int32 pE = 5;
inline bool HighScore::_internal_has_pe() const {
  bool value = (_has_bits_[0] & 0x00000010u) != 0;
  return value;
}
inline bool HighScore::has_pe() const {
  return _internal_has_pe();
}
inline void HighScore::clear_pe() {
  pe_ = 0;
  _has_bits_[0] &= ~0x00000010u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 HighScore::_internal_pe() const {
  return pe_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 HighScore::pe() const {
  // @@protoc_insertion_point(field_get:HighScore.pE)
  return _internal_pe();
}
inline void HighScore::_internal_set_pe(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000010u;
  pe_ = value;
}
inline void HighScore::set_pe(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_pe(value);
  // @@protoc_insertion_point(field_set:HighScore.pE)
}

// optional int32 pF = 6;
inline bool HighScore::_internal_has_pf() const {
  bool value = (_has_bits_[0] & 0x00000020u) != 0;
  return value;
}
inline bool HighScore::has_pf() const {
  return _internal_has_pf();
}
inline void HighScore::clear_pf() {
  pf_ = 0;
  _has_bits_[0] &= ~0x00000020u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 HighScore::_internal_pf() const {
  return pf_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 HighScore::pf() const {
  // @@protoc_insertion_point(field_get:HighScore.pF)
  return _internal_pf();
}
inline void HighScore::_internal_set_pf(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000020u;
  pf_ = value;
}
inline void HighScore::set_pf(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_pf(value);
  // @@protoc_insertion_point(field_set:HighScore.pF)
}

// optional int32 pG = 7;
inline bool HighScore::_internal_has_pg() const {
  bool value = (_has_bits_[0] & 0x00000040u) != 0;
  return value;
}
inline bool HighScore::has_pg() const {
  return _internal_has_pg();
}
inline void HighScore::clear_pg() {
  pg_ = 0;
  _has_bits_[0] &= ~0x00000040u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 HighScore::_internal_pg() const {
  return pg_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 HighScore::pg() const {
  // @@protoc_insertion_point(field_get:HighScore.pG)
  return _internal_pg();
}
inline void HighScore::_internal_set_pg(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000040u;
  pg_ = value;
}
inline void HighScore::set_pg(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_pg(value);
  // @@protoc_insertion_point(field_set:HighScore.pG)
}

// optional int32 pH = 8;
inline bool HighScore::_internal_has_ph() const {
  bool value = (_has_bits_[0] & 0x00000080u) != 0;
  return value;
}
inline bool HighScore::has_ph() const {
  return _internal_has_ph();
}
inline void HighScore::clear_ph() {
  ph_ = 0;
  _has_bits_[0] &= ~0x00000080u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 HighScore::_internal_ph() const {
  return ph_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 HighScore::ph() const {
  // @@protoc_insertion_point(field_get:HighScore.pH)
  return _internal_ph();
}
inline void HighScore::_internal_set_ph(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000080u;
  ph_ = value;
}
inline void HighScore::set_ph(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_ph(value);
  // @@protoc_insertion_point(field_set:HighScore.pH)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_high_5fscore_2eproto
