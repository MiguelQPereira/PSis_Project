/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: high_score.proto */

#ifndef PROTOBUF_C_high_5fscore_2eproto__INCLUDED
#define PROTOBUF_C_high_5fscore_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1000000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003003 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _HighScore HighScore;


/* --- enums --- */


/* --- messages --- */

struct  _HighScore
{
  ProtobufCMessage base;
  protobuf_c_boolean has_num;
  int32_t num;
};
#define HIGH_SCORE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&high_score__descriptor) \
    , 0, 0 }


/* HighScore methods */
void   high_score__init
                     (HighScore         *message);
size_t high_score__get_packed_size
                     (const HighScore   *message);
size_t high_score__pack
                     (const HighScore   *message,
                      uint8_t             *out);
size_t high_score__pack_to_buffer
                     (const HighScore   *message,
                      ProtobufCBuffer     *buffer);
HighScore *
       high_score__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   high_score__free_unpacked
                     (HighScore *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*HighScore_Closure)
                 (const HighScore *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor high_score__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_high_5fscore_2eproto__INCLUDED */
