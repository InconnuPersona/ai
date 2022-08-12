#pragma once

#include "net.h"

namespace net {
	enum http_method_e {
		HTTP_GET,
		HTTP_HEAD,
		HTTP_POST,
		HTTP_PUT,
		HTTP_DELETE,
		HTTP_CONNECT,
		HTTP_OPTIONS,
		HTTP_TRACE,
		HTTP_PATCH
	};
	
	enum http_version_e {
		HTTP_0_9 = 9;
		HTTP_1_0 = 10,
		HTTP_1_1 = 11,
		HTTP_2_0 = 20
	};
	
	enum http_status_e {
		
		HTTP_OK = 200,
		
		HTTP_FORBIDDEN = 403,
		HTTP_NOT_FOUND = 404,
		
		HTTP_BAD_GATEWAY = 502,
		HTTP_VERSION_NOT_SUPPORTED = 505,
	};
	
	struct http_uri_s {
		string_t path;
		string_t scheme;
		string_t host;
		short port;
		
		
	};
	
	struct http_msg_s {
		http_version_e version;
		std::map<string_t, string_t> headers;
		
		string_t content;
	};
	
	struct http_request_s : http_msg_s {
		http_method_e method;
		http_uri_s uri;
	};
	
	struct http_response_s : http_msg_s {
		http_status_e status;
	};
	
	
}
