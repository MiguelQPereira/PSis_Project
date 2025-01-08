// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: high_score.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_high_5fscore_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_high_5fscore_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021012 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
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
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_high_5fscore_2eproto;
class HighScore;
struct HighScoreDefaultTypeInternal;
extern HighScoreDefaultTypeInternal _HighScore_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::HighScore* Arena::CreateMaybeMessage<::HighScore>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

// ===================================================================

class HighScore final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:HighScore) */ {
 public:
  inline HighScore() : HighScore(nullptr) {}
  ~HighScore() override;
  explicit PROTOBUF_CONSTEXPR HighScore(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

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
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
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
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const HighScore& default_instance() {
    return *internal_default_instance();
  }
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
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(HighScore* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  HighScore* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<HighScore>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const HighScore& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const HighScore& from) {
    HighScore::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(HighScore* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "HighScore";
  }
  protected:
  explicit HighScore(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

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
  int32_t pa() const;
  void set_pa(int32_t value);
  private:
  int32_t _internal_pa() const;
  void _internal_set_pa(int32_t value);
  public:

  // optional int32 pB = 2;
  bool has_pb() const;
  private:
  bool _internal_has_pb() const;
  public:
  void clear_pb();
  int32_t pb() const;
  void set_pb(int32_t value);
  private:
  int32_t _internal_pb() const;
  void _internal_set_pb(int32_t value);
  public:

  // optional int32 pC = 3;
  bool has_pc() const;
  private:
  bool _internal_has_pc() const;
  public:
  void clear_pc();
  int32_t pc() const;
  void set_pc(int32_t value);
  private:
  int32_t _internal_pc() const;
  void _internal_set_pc(int32_t value);
  public:

  // optional int32 pD = 4;
  bool has_pd() const;
  private:
  bool _internal_has_pd() const;
  public:
  void clear_pd();
  int32_t pd() const;
  void set_pd(int32_t value);
  private:
  int32_t _internal_pd() const;
  void _internal_set_pd(int32_t value);
  public:

  // optional int32 pE = 5;
  bool has_pe() const;
  private:
  bool _internal_has_pe() const;
  public:
  void clear_pe();
  int32_t pe() const;
  void set_pe(int32_t value);
  private:
  int32_t _internal_pe() const;
  void _internal_set_pe(int32_t value);
  public:

  // optional int32 pF = 6;
  bool has_pf() const;
  private:
  bool _internal_has_pf() const;
  public:
  void clear_pf();
  int32_t pf() const;
  void set_pf(int32_t value);
  private:
  int32_t _internal_pf() const;
  void _internal_set_pf(int32_t value);
  public:

  // optional int32 pG = 7;
  bool has_pg() const;
  private:
  bool _internal_has_pg() const;
  public:
  void clear_pg();
  int32_t pg() const;
  void set_pg(int32_t value);
  private:
  int32_t _internal_pg() const;
  void _internal_set_pg(int32_t value);
  public:

  // optional int32 pH = 8;
  bool has_ph() const;
  private:
  bool _internal_has_ph() const;
  public:
  void clear_ph();
  int32_t ph() const;
  void set_ph(int32_t value);
  private:
  int32_t _internal_ph() const;
  void _internal_set_ph(int32_t value);
  public:

  // optional int32 game = 9;
  bool has_game() const;
  private:
  bool _internal_has_game() const;
  public:
  void clear_game();
  int32_t game() const;
  void set_game(int32_t value);
  private:
  int32_t _internal_game() const;
  void _internal_set_game(int32_t value);
  public:

  // @@protoc_insertion_point(class_scope:HighScore)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
    int32_t pa_;
    int32_t pb_;
    int32_t pc_;
    int32_t pd_;
    int32_t pe_;
    int32_t pf_;
    int32_t pg_;
    int32_t ph_;
    int32_t game_;
  };
  union { Impl_ _impl_; };
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
  bool value = (_impl_._has_bits_[0] & 0x00000100u) != 0;
  return value;
}
inline bool HighScore::has_game() const {
  return _internal_has_game();
}
inline void HighScore::clear_game() {
  _impl_.game_ = 0;
  _impl_._has_bits_[0] &= ~0x00000100u;
}
inline int32_t HighScore::_internal_game() const {
  return _impl_.game_;
}
inline int32_t HighScore::game() const {
  // @@protoc_insertion_point(field_get:HighScore.game)
  return _internal_game();
}
inline void HighScore::_internal_set_game(int32_t value) {
  _impl_._has_bits_[0] |= 0x00000100u;
  _impl_.game_ = value;
}
inline void HighScore::set_game(int32_t value) {
  _internal_set_game(value);
  // @@protoc_insertion_point(field_set:HighScore.game)
}

// optional int32 pA = 1;
inline bool HighScore::_internal_has_pa() const {
  bool value = (_impl_._has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool HighScore::has_pa() const {
  return _internal_has_pa();
}
inline void HighScore::clear_pa() {
  _impl_.pa_ = 0;
  _impl_._has_bits_[0] &= ~0x00000001u;
}
inline int32_t HighScore::_internal_pa() const {
  return _impl_.pa_;
}
inline int32_t HighScore::pa() const {
  // @@protoc_insertion_point(field_get:HighScore.pA)
  return _internal_pa();
}
inline void HighScore::_internal_set_pa(int32_t value) {
  _impl_._has_bits_[0] |= 0x00000001u;
  _impl_.pa_ = value;
}
inline void HighScore::set_pa(int32_t value) {
  _internal_set_pa(value);
  // @@protoc_insertion_point(field_set:HighScore.pA)
}

// optional int32 pB = 2;
inline bool HighScore::_internal_has_pb() const {
  bool value = (_impl_._has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool HighScore::has_pb() const {
  return _internal_has_pb();
}
inline void HighScore::clear_pb() {
  _impl_.pb_ = 0;
  _impl_._has_bits_[0] &= ~0x00000002u;
}
inline int32_t HighScore::_internal_pb() const {
  return _impl_.pb_;
}
inline int32_t HighScore::pb() const {
  // @@protoc_insertion_point(field_get:HighScore.pB)
  return _internal_pb();
}
inline void HighScore::_internal_set_pb(int32_t value) {
  _impl_._has_bits_[0] |= 0x00000002u;
  _impl_.pb_ = value;
}
inline void HighScore::set_pb(int32_t value) {
  _internal_set_pb(value);
  // @@protoc_insertion_point(field_set:HighScore.pB)
}

// optional int32 pC = 3;
inline bool HighScore::_internal_has_pc() const {
  bool value = (_impl_._has_bits_[0] & 0x00000004u) != 0;
  return value;
}
inline bool HighScore::has_pc() const {
  return _internal_has_pc();
}
inline void HighScore::clear_pc() {
  _impl_.pc_ = 0;
  _impl_._has_bits_[0] &= ~0x00000004u;
}
inline int32_t HighScore::_internal_pc() const {
  return _impl_.pc_;
}
inline int32_t HighScore::pc() const {
  // @@protoc_insertion_point(field_get:HighScore.pC)
  return _internal_pc();
}
inline void HighScore::_internal_set_pc(int32_t value) {
  _impl_._has_bits_[0] |= 0x00000004u;
  _impl_.pc_ = value;
}
inline void HighScore::set_pc(int32_t value) {
  _internal_set_pc(value);
  // @@protoc_insertion_point(field_set:HighScore.pC)
}

// optional int32 pD = 4;
inline bool HighScore::_internal_has_pd() const {
  bool value = (_impl_._has_bits_[0] & 0x00000008u) != 0;
  return value;
}
inline bool HighScore::has_pd() const {
  return _internal_has_pd();
}
inline void HighScore::clear_pd() {
  _impl_.pd_ = 0;
  _impl_._has_bits_[0] &= ~0x00000008u;
}
inline int32_t HighScore::_internal_pd() const {
  return _impl_.pd_;
}
inline int32_t HighScore::pd() const {
  // @@protoc_insertion_point(field_get:HighScore.pD)
  return _internal_pd();
}
inline void HighScore::_internal_set_pd(int32_t value) {
  _impl_._has_bits_[0] |= 0x00000008u;
  _impl_.pd_ = value;
}
inline void HighScore::set_pd(int32_t value) {
  _internal_set_pd(value);
  // @@protoc_insertion_point(field_set:HighScore.pD)
}

// optional int32 pE = 5;
inline bool HighScore::_internal_has_pe() const {
  bool value = (_impl_._has_bits_[0] & 0x00000010u) != 0;
  return value;
}
inline bool HighScore::has_pe() const {
  return _internal_has_pe();
}
inline void HighScore::clear_pe() {
  _impl_.pe_ = 0;
  _impl_._has_bits_[0] &= ~0x00000010u;
}
inline int32_t HighScore::_internal_pe() const {
  return _impl_.pe_;
}
inline int32_t HighScore::pe() const {
  // @@protoc_insertion_point(field_get:HighScore.pE)
  return _internal_pe();
}
inline void HighScore::_internal_set_pe(int32_t value) {
  _impl_._has_bits_[0] |= 0x00000010u;
  _impl_.pe_ = value;
}
inline void HighScore::set_pe(int32_t value) {
  _internal_set_pe(value);
  // @@protoc_insertion_point(field_set:HighScore.pE)
}

// optional int32 pF = 6;
inline bool HighScore::_internal_has_pf() const {
  bool value = (_impl_._has_bits_[0] & 0x00000020u) != 0;
  return value;
}
inline bool HighScore::has_pf() const {
  return _internal_has_pf();
}
inline void HighScore::clear_pf() {
  _impl_.pf_ = 0;
  _impl_._has_bits_[0] &= ~0x00000020u;
}
inline int32_t HighScore::_internal_pf() const {
  return _impl_.pf_;
}
inline int32_t HighScore::pf() const {
  // @@protoc_insertion_point(field_get:HighScore.pF)
  return _internal_pf();
}
inline void HighScore::_internal_set_pf(int32_t value) {
  _impl_._has_bits_[0] |= 0x00000020u;
  _impl_.pf_ = value;
}
inline void HighScore::set_pf(int32_t value) {
  _internal_set_pf(value);
  // @@protoc_insertion_point(field_set:HighScore.pF)
}

// optional int32 pG = 7;
inline bool HighScore::_internal_has_pg() const {
  bool value = (_impl_._has_bits_[0] & 0x00000040u) != 0;
  return value;
}
inline bool HighScore::has_pg() const {
  return _internal_has_pg();
}
inline void HighScore::clear_pg() {
  _impl_.pg_ = 0;
  _impl_._has_bits_[0] &= ~0x00000040u;
}
inline int32_t HighScore::_internal_pg() const {
  return _impl_.pg_;
}
inline int32_t HighScore::pg() const {
  // @@protoc_insertion_point(field_get:HighScore.pG)
  return _internal_pg();
}
inline void HighScore::_internal_set_pg(int32_t value) {
  _impl_._has_bits_[0] |= 0x00000040u;
  _impl_.pg_ = value;
}
inline void HighScore::set_pg(int32_t value) {
  _internal_set_pg(value);
  // @@protoc_insertion_point(field_set:HighScore.pG)
}

// optional int32 pH = 8;
inline bool HighScore::_internal_has_ph() const {
  bool value = (_impl_._has_bits_[0] & 0x00000080u) != 0;
  return value;
}
inline bool HighScore::has_ph() const {
  return _internal_has_ph();
}
inline void HighScore::clear_ph() {
  _impl_.ph_ = 0;
  _impl_._has_bits_[0] &= ~0x00000080u;
}
inline int32_t HighScore::_internal_ph() const {
  return _impl_.ph_;
}
inline int32_t HighScore::ph() const {
  // @@protoc_insertion_point(field_get:HighScore.pH)
  return _internal_ph();
}
inline void HighScore::_internal_set_ph(int32_t value) {
  _impl_._has_bits_[0] |= 0x00000080u;
  _impl_.ph_ = value;
}
inline void HighScore::set_ph(int32_t value) {
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
