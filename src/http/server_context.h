// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef SRC_HTTP_SERVER_CONTEXT_H_
#define SRC_HTTP_SERVER_CONTEXT_H_

#include <http_parser.h>
#include <uv.h>

#include "./server_request_impl.h"
#include "./server_response_impl.h"
#include "../net/socket_impl.h"

namespace libj {
namespace node {
namespace http {

class ServerContext {
 public:
    ServerContext(void* srv)
        : server(srv)
        , socket(net::SocketImpl::create())
        , request(LIBJ_NULL(ServerRequestImpl))
        , response(LIBJ_NULL(ServerResponseImpl)) {
    }

    http_parser parser;
    void* server;
    net::SocketImpl::Ptr socket;
    ServerRequestImpl::Ptr request;
    ServerResponseImpl::Ptr response;
};

}  // namespace http
}  // namespace node
}  // namespace libj

#endif  // SRC_HTTP_SERVER_CONTEXT_H_
