#pragma once

enum NodeType : int {
	NODE_NONE = 0,
	NODE_STAR = 1,
	NODE_LAND = 2, // Planet, layers of planet, binary planets, or moons.
	NODE_PROV = 3,
};

/*struct addr_s {
	node_s::id_t star;
	node_s::id_t land;
	node_s::id_t prov;
};*/
