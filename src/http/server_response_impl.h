// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef SRC_HTTP_SERVER_RESPONSE_IMPL_H_
#define SRC_HTTP_SERVER_RESPONSE_IMPL_H_

#include <libj/string_buffer.h>
#include <string.h>
#include <uv.h>
#include <string>

#include "libnode/http/server_response.h"
#include "libnode/http/status.h"

namespace libj {
namespace node {
namespace http {

class ServerContext;

class ServerResponseImpl : public ServerResponse {
 private:
    static const String::CPtr HEADERS;
    static const String::CPtr STATUS_CODE;

 public:
    typedef LIBJ_PTR(ServerResponseImpl) Ptr;

    Boolean writeHead(Int statusCode) {
        status_ = http::Status::create(statusCode);
        if (status_) {
            put(STATUS_CODE, statusCode);
            return true;
        } else {
            return false;
        }
    }

    Int statusCode() const {
        if (status_) {
            return status_->code();
        } else {
            return 0;
        }
    }

    JsObject::Ptr getHeaders() {
        JsObject::Ptr headers = getPtr<JsObject>(HEADERS);
        if (!headers) {
            headers = JsObject::create();
            put(HEADERS, headers);
        }
        return headers;
    }

    void setHeader(String::CPtr name, String::CPtr value) {
        getHeaders()->put(name, value);
    }

    String::CPtr getHeader(String::CPtr name) const {
        JsObject::Ptr headers = getPtr<JsObject>(HEADERS);
        if (headers) {
            Value v = headers->get(name);
            return toCPtr<String>(v);
        } else {
            LIBJ_NULL_CPTR(String, nullp);
            return nullp;
        }
    }

    void removeHeader(String::CPtr name) {
        getHeaders()->remove(name);
    }

    void write(String::CPtr chunk, String::Encoding enc) {
        body_->append(chunk);
    }

    void makeResponse() {
        res_->append(String::create("HTTP/1.1 "));
        if (status_) {
            res_->append(String::valueOf(status_->code()));
            res_->append(String::create(" "));
            res_->append(status_->toString());
            res_->append(String::create("\r\n"));
        } else {
            res_->append(String::create("200 OK\r\n"));
        }
        Int len = body_->length();
        setHeader(
            String::create("Content-Length"),
            String::valueOf(len));
        String::CPtr colon = String::create(": ");
        String::CPtr nl = String::create("\r\n");
        JsObject::Ptr headers = getHeaders();
        Set::CPtr ks = headers->keySet();
        Iterator::Ptr itr = ks->iterator();
        while (itr->hasNext()) {
            String::CPtr name = toCPtr<String>(itr->next());
            String::CPtr value = toCPtr<String>(headers->get(name));
            res_->append(name);
            res_->append(colon);
            res_->append(value);
            res_->append(nl);
        }
        res_->append(nl);
        res_->append(body_);
    }

    void write(Buffer::CPtr buf) {
        // TODO(plenluno): implement
    }

    Boolean end();

    Boolean destroy() {
        // TODO(plenluno): implement
        return false;
    }

    Boolean destroySoon() {
        // TODO(plenluno): implement
        return false;
    }

    Boolean writable() const {
        // TODO(plenluno): implement
        return true;
    }

 private:
    ServerContext* context_;

    http::Status::CPtr status_;

    // TODO(plenluno): introduce Buffer
    StringBuffer::Ptr res_;
    StringBuffer::Ptr body_;

    EventEmitter::Ptr ee_;

 public:
    ServerResponseImpl(ServerContext* context);

    LIBNODE_EVENT_EMITTER_IMPL(ee_);
};

}  // namespace http
}  // namespace node
}  // namespace libj

#endif  // SRC_HTTP_SERVER_RESPONSE_IMPL_H_
