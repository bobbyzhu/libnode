// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBNODE_UTIL_H_
#define LIBNODE_UTIL_H_

#include <libj/string.h>

#include "libnode/buffer.h"

namespace libj {
namespace node {
namespace util {

Boolean isArray(const Value& val);
Boolean isError(const Value& val);
Boolean isRegExp(const Value& val);

String::CPtr hexEncode(Buffer::CPtr buf);
Buffer::Ptr hexDecode(String::CPtr str);

String::CPtr base64Encode(Buffer::CPtr buf);
Buffer::Ptr base64Decode(String::CPtr str);

String::CPtr percentEncode(
    String::CPtr str, Buffer::Encoding enc = Buffer::UTF8);
String::CPtr percentDecode(
    String::CPtr str, Buffer::Encoding enc = Buffer::UTF8);

}  // namespace util
}  // namespace node
}  // namespace libj

#endif  // LIBNODE_UTIL_H_
