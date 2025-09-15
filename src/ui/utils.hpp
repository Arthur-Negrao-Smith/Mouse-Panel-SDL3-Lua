/*
File with util structures
*/

#ifndef UTILS_PAANEL_SDL3_LUA
#define UTILS_PAANEL_SDL3_LUA

#include <cstdint>

typedef struct {
  int x, y;

} Position;

typedef struct {
  int width, height;
} Geometry;

typedef struct {
  uint8_t r, g, b;
  float alpha;
} Color;

#endif
