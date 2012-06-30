// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBNODE_HTTP_SERVER_REQUEST_H_
#define LIBNODE_HTTP_SERVER_REQUEST_H_

#include "libnode/net/socket.h"

namespace libj {
namespace node {
namespace http {

class ServerRequest : LIBNODE_EVENT_EMITTER(ServerRequest)
 public:
    static const String::CPtr EVENT_DATA;
    static const String::CPtr EVENT_END;
    static const String::CPtr EVENT_CLOSE;

    virtual String::CPtr method() const = 0;
    virtual String::CPtr url() const = 0;
    virtual JsObject::CPtr headers() const = 0;
    virtual String::CPtr httpVersion() const = 0;
    virtual net::Socket::Ptr connection() const = 0;
};

}  // namespace http
}  // namespace node
}  // namespace libj

#endif  // LIBNODE_HTTP_SERVER_REQUEST_H_
