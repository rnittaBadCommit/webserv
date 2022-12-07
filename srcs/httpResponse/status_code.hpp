//
// Created by yuumo on 2022/10/14.
//

#ifndef WEBSERV_SRCS_STATUS_CODE_HPP_
#define WEBSERV_SRCS_STATUS_CODE_HPP_

/*
 * https://developer.mozilla.org/ja/docs/Web/HTTP/Status
 */

#define HTTP_CONTINUE                   100
#define HTTP_SWITCHING_PROTOCOLS        101

#define HTTP_OK                         200
#define HTTP_CREATED                    201
#define HTTP_ACCEPTED                   202
// Non-Authoritative Information
#define HTTP_NO_CONTENT                 204
// Reset Content
#define HTTP_PARTIAL_CONTENT            206

#define HTTP_SPECIAL_RESPONSE           300
#define HTTP_MOVED_PERMANENTLY          301
#define HTTP_MOVED_TEMPORARILY          302
#define HTTP_SEE_OTHER                  303
#define HTTP_NOT_MODIFIED               304
// Use Proxy
#define HTTP_TEMPORARY_REDIRECT         307
#define HTTP_PERMANENT_REDIRECT         308

#define HTTP_BAD_REQUEST                400
#define HTTP_UNAUTHORIZED               401
#define HTTP_FORBIDDEN                  403
#define HTTP_NOT_FOUND                  404
#define HTTP_NOT_ALLOWED                405
// Not Acceptable
// Proxy Authentication Required
#define HTTP_REQUEST_TIME_OUT           408
#define HTTP_CONFLICT                   409
#define HTTP_LENGTH_REQUIRED            411
#define HTTP_PRECONDITION_FAILED        412
#define HTTP_REQUEST_ENTITY_TOO_LARGE   413
#define HTTP_REQUEST_URI_TOO_LARGE      414
#define HTTP_UNSUPPORTED_MEDIA_TYPE     415
#define HTTP_RANGE_NOT_SATISFIABLE      416
// Expectation Failed                   417
// Upgrade Required                     426

#define HTTP_INTERNAL_SERVER_ERROR      500
#define HTTP_NOT_IMPLEMENTED            501
#define HTTP_BAD_GATEWAY                502
#define HTTP_SERVICE_UNAVAILABLE        503
#define HTTP_GATEWAY_TIME_OUT           504
#define HTTP_VERSION_NOT_SUPPORTED      505

#endif //WEBSERV_SRCS_STATUS_CODE_HPP_
