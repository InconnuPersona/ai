#pragma once

#include <map>
#include <set>
#include <unordered_map>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#ifdef _WIN32
 #include "SDL2/SDL.h"
#else
 #include <SDL2/SDL.h>
#endif

using glm::vec2;
using glm::vec3;
using glm::vec4;

using glm::ivec2;
using glm::ivec3;

typedef glm::ivec2 vec2i;
typedef glm::ivec3 vec3i;

using glm::mat4;

template <typename T1, typename T2>
using hashmap_t = std::unordered_map<T1, T2>;

template <typename T>
using vector_t = std::vector<T>;

typedef unsigned char byte_t;
typedef long long long_t;
typedef std::string string_t;
typedef const string_t cstring_t;

typedef SDL_Surface* surface_t;
typedef SDL_Texture* texture_t;

template <typename T1, typename T2>
struct tuple_s {
 T1 key;
 T2 e; // element.
};

template <typename T1, typename T2>
using map_t = std::map<T1, T2>;

template <typename T1, typename T2>
using tuplemap_t = vector_t<tuple_s<T1, T2>>;

template <typename T1, typename T2>
using multimap_t = std::multimap<T1, T2>;
