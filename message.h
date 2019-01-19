#pragma once

#include "base.h"

typedef enum {
 MESSAGE_UNKNOWN,
 MESSAGE_NONE,
 MESSAGE_INPUT,
 MESSAGE_QUERY,
} message_type_e;

typedef struct {
 uint length;
 uint type;
 pointer_t data;
} message_t;
