#include "jsmn.h"

#include "text.h"

/*const size_t json_s::initial_count = 64;

json_s::json_s() : tokens(initial_count, tok_s(*this)) {

}

json_s::json_s(cstring_t& text) {

	parse(text);

}

json_s::~json_s() {
	tokens.clear();
}

void json_s::parse(cstring_t& text) {
	jsmn_parser parser;
	jsmntok_t* tok;
	int count;
	int i, r;
	int stack[10];
	int sp;

	jsmn_init(&parser);

	count = initial_count;

	tok = NULL;

loop:
	tok = (jsmntok_t*) realloc(tok, sizeof(*tok) * count);

	if (!tok) {
		ERROR("unable to allocate %i jsmn tokens.", count);
	}

	r = jsmn_parse(&parser, text.c_str(), text.length(), tok, count);

	if (r == JSMN_ERROR_NOMEM) {
		count *= 2;

		goto loop;
	}
	elif (r == JSMN_ERROR_INVAL) {
		ERROR("bad token in JSON.");
	}
	elif (r == JSMN_ERROR_PART) {
		ERROR("open end of JSON file reached.");
	}
	elif (r < 0) {
		ERROR("unknown JSON error encountered.");
	}

	/*sp = -1;

	for (i = 0; i < r; i++) {
		if (tok[i].type == JSMN_PRIMITIVE || tok[i].type == JSMN_STRING) {

		}
		elif (tok[i].type == JSMN_ARRAY || tok[i].type == JSMN_OBJECT) {

		}
		else {
			ERROR("");
		}
	}*//*

	for (i = 0; i < r; i++) {
		printf("%i: %.*s\n", tok[i].end - tok[i].start, &text[tok[i].start]);

		if (tok[i].type == JSMN_ARRAY || tok[i].type == JSMN_OBJECT) {
			printf(" {%i\n", tok[i].size);
		}
	}
}
*/