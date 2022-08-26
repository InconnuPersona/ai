#pragma once

#define DEFINE_IDEA(Name) struct Name##Idea : eco::idea_s

// Builtin ideas

DEFINE_IDEA(PopEthnic) {
	eco::pop_ethnic_s::id_t primary;
	eco::pop_ethnic_s::id_t accepted;
};

DEFINE_IDEA(PopClass) {
	cardinal = true;
};

DEFINE_IDEA(PopFaith) {
	cardinal = true;
};
