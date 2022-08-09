#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "image.h"

image_s::image_s() : ch(0), data(0), w(0), h(0) {
}

image_s::image_s(int w, int h) : w(w), h(h) {
	data = new color_s[w * h];
	ch = 4;

	if (!data) {
		ERROR("unable to create image of size %i by %i.", w, h);
	}
}

image_s::image_s(cstring_t& path) {
	ch = STBI_rgb_alpha;

	data = (color_s*) stbi_load(path.c_str(), &w, &h, NULL, ch);

	if (!data) {
		ERROR("unable load image '%s'.", path.c_str());
	}
}

image_s::~image_s() {
	if (data) {
		stbi_image_free((byte_t*) data);
	}
}

void image_s::save(cstring_t& path) {
	if (data) {
		if (!stbi_write_png(path.c_str(), w, h, ch, data, w * ch)) {
			ERROR("unable to write image to '%s'.", path.c_str());
		}
	}
	else {
		ERROR("unable to write null image to '%s'.", path.c_str());
	}
}
