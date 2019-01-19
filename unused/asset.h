#pragma once

#include "base.h"

typedef struct
asset_s {
 MAKE_LINK(asset);
 
 string_t type;
 string_t label;
 
 pointer_t pointer;
} asset_t;

typedef struct
asset_holder_s {
 asset_t* assets;
} asset_holder_t;
