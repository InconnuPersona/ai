#pragma once

#include "ns/object.h"
#include "message.h"

#define CLASS_ENTITY \
 string_t class; \
 object_t* object;

typedef struct {
 CLASS_ENTITY;
 
 void (*receive)(message_t* message);
} entity_t;

typedef entity_t* entity_p;


