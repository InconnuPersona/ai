#pragma once

#include "base.h"

#include "stb_image.h"
#include "stb_image_write.h"

struct image_s {
	int w, h;
	int ch;
	const color_s* data;

	image_s();
	image_s(int w, int h);
	image_s(cstring_t& path);
	~image_s();

	void save(cstring_t& path);
};
