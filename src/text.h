#pragma once

#include "base.h"

#include <fstream>

#define READ_FILE(Path, Out) \
{ \
	std::ifstream in(Path); \
	std::stringstream ss; \
	ss << in.rdbuf(); \
	Out = ss.str(); \
}

struct source_s;

struct token_s {
private:
	source_s* source;
	
	int from, prev;
	
	friend source_s;
	
public:
	token_s(source_s* source);
	
	string_t get();
	string_t get(size_t index);
	string_t get(cstring_t& name);
	
	// Gets the number of elements falling under this
	// token.
	int size();
	
	// If there is another token after this, skip to it,
	// otherwise it will return false.
	bool next();
};

struct source_s {
private:
	vector_t<token_s> tokens;
	
	
	
	void parse_file(cstring_t& path);
	void parse_text(cstring_t& text);
};
