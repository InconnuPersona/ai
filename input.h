#pragma once

#include "base.h"

#define MAX_INPUT_BUFFER_ELEMENTS 128
#define MAX_INPUT_ELEMENT_SZ 32

#define CLASS_INPUT_ELEMENT \
 MAKE_LINK(input_element); \
 input_type_e type; \
 string_t label;

typedef enum {
 INPUT_END,
 INPUT_KEY,
 INPUT_POINTER,
 INPUT_WHEEL,
} input_type_e;

typedef enum {
 RELEASE,
 PRESS
} key_state_e;

typedef struct {
 CLASS_INPUT_ELEMENT;
} input_element_t;

typedef input_element_t* input_element_p;

typedef struct {
 CLASS_INPUT_ELEMENT;
 
 float time;
 int code;
 key_state_e state;
} input_key_t;

typedef input_key_t* input_key_p;

typedef struct {
 CLASS_INPUT_ELEMENT;
 
 vector2f_t position;
 vector2f_t delta;
} input_pointer_t;

typedef struct
input_s {
 input_key_t* key_map;
 
 input_element_p* elements;
 input_element_t* buffer;
} input_t;

void init_input(input_t* input);

boolean_t get_input_key(input_key_t** key, string_t label, input_t* input);
boolean_t set_input_key(input_key_t* key, input_t* input);

boolean_t get_input_element(input_element_t* element, input_t* input, string_t label);
boolean_t set_input_element();

void receive_input();
