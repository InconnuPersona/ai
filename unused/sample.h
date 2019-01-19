#pragma once

#include "entity.h"

/*
Samples, such as populations, produce, materials, or otherwise, are represented into divisible
units that belong to a class of entity. These samples may be grouped or divided, so long there
remain limited population size, and may be distributed across tiles. Single count samples are
considered as lone species, hence allowing them to remain indistributable or controllable by an
entity.
*/

#define CLASS_SAMPLE

typedef struct {
 CLASS_ENTITY;
 
 uint count;
 entity_p entity;
} sample_unit_t;

typedef struct {
 sample_unit_t* units;
} sample_t;

typedef struct {
 
} sampler_t;
