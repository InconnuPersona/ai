#pragma once

#include "net.h"

namespace net {

	struct udp_client_s : client_s {

	};

	struct udp_server_s : server_s {
		int sock;
	};

}
