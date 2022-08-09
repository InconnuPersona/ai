#include "map/map.h"

map::map_s world;

#undef main

enum terr_e : byte_t {
	TERR_LAND = 255,
	TERR_SEA = 0,
};

struct tile_s {
	byte_t height;
	byte_t terrain;
};

int map_w, map_h;
tile_s* tiles;

double vsqrt(double a) {
	int64_t i;
	double x, y;

	x = a * 0.5f;
	y = a;
	i = *(int64_t*) &y;
	i = 0x5FE6EB50C7B537A9 - (i >> 1);
	y = *(double*) &i;
	y = y * (1.5f - (x * y * y));

	return (1.f / y);
}

double rand_double() {
	return (double) rand() / RAND_MAX;
}

void gen_map(int w, int h, int in_passes, int sea) {
	double ph, pw, px, py;
	int points;
	int passes;
	int i, x, y;

	tiles = new tile_s[w * h];

	for (i = 0; i < w * h; i++) {
		tiles[i].height = 0;
	}

	passes = in_passes;

	while (passes) {
		points = (w * h) / ((w + h) * passes);

		printf("pass %i points: %i\n", passes, points);

		while (points) {
			px = rand() % w;
			py = rand() % h;
			
			// weight/area of effect
			pw = (double) passes / in_passes;
			
			
			pw += 1;
			ph = sea * (pw + pw) / (pw * pw);
			pw *= (double) (w + h) / 2;

			for (i = 0; i < w * h; i++) {
				y = i / w;
				x = i - (y * w);

				x -= px;
				y -= py;

				double m = vsqrt((x * x) + (y * y)) / pw;

				tiles[i].height += (byte_t) (/*rand_double() */ m * ph);
			}

			points--;
		}

		passes--;
	}

	for (i = 0; i < w * h; i++) {
		terr_e terr;

		if (tiles[i].height > (byte_t) (255 / sea * 16)) {
			terr = TERR_LAND;
		}
		else {
			terr = TERR_SEA;
		}

		tiles[i].terrain = (byte_t) terr;
	}

	map_w = w;
	map_h = h;
}

#define WRITE(File, Element) \
{ \
	byte_t* data = new byte_t[map_w * map_h]; \
	for (int i = 0; i < map_w * map_h; i++) { \
		data[i] = tiles[i].Element; \
	} \
	stbi_write_png(File, map_w, map_h, STBI_grey, data, map_w * STBI_grey); \
}

int main(int argc, char** argv) {

	string_t s;

	srand(time(NULL));

	gen_map(128, 128, 4, 10);

	WRITE("height.png", height);
	WRITE("terrain.png", terrain);

	/*for (int i = 0; i < 50; i++) {
		s = "height" + std::to_string(i) + ".png";
		
		gen_map(128, 128, i, 10);

		WRITE(s.c_str(), height);
	}*/

	for (int i = 0; i < map_w * map_h; i++) {
		tiles[i].height = rand() % 255;
	}

	WRITE("random.png", height);

	//getc(stdin);

	return 0;
}
