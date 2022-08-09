#pragma once

#include "base.h"

namespace eco {

	struct good_s : comp_s {

	};

	struct item_s {
		good_s::id_t good;
		float count;

	};

	struct pile_s {
		vector_t<item_s> items;


	};
}


/*enum good_e {
 GOOD_UNKNOWN = 0,
 GOOD_COIN,
 GOOD_FOOD,
 GOOD_LUXURY,
 GOOD_MATERIAL,
 GOOD_METAL,
 GOOD_WORK
};

// Goods are cloned by ID to each pile, and assigned their values.
// The default goods maintain the original prices.
struct good_s : public comp_s {
 string_t name;
 good_e type;
 
 float value;
 
 bool banned;
};

struct item_s {
 int good;
 float count;
 
 item_s(good_e good, int count = 1);
};

// All piles are registered into the global pile table.
struct pile_s {
 vector_t<item_s> items;
 
 //multimap_t<tag_s, item_s> demands;
 
 pile_s();
 
};

enum market_e {
 MARKET_CLOSED = 0,
 MARKET_OPEN,
 MARKET_CLASS
};

// Markets are designated over nodes and cities.
struct market_s : public comp_s {
 vector_t<good_s> goods;
 
 // Stockpile of goods.
 pile_s stock;
 
 void ban_good();
 void allow_good();
 void embargo(tag_s tag);
 
 void close();
 void reopen();
 
};*/
