/*
File with util structures
*/

#ifndef UTILS_PAANEL_SDL3_LUA
#define UTILS_PAANEL_SDL3_LUA

#include <cstdint>

/*
 * @brief Constant to define the app name
 */
#define APP_NAME "Mouse Panel"

/*
 * @brief Constant to compare color selected
 */
#define DEFAULT_BUTTON_FONT_COLOR "default"

/*
 * @brief Constant to define default button height
 */
#define DEFAULT_BUTTON_HEIGHT 30

/*
 * @brief Constant to define default width of the popup menu
 */
#define DEFAULT_WIDTH_POPUP 200

/*
 * @brief Constante to define default height of the popup menu
 */
#define DEFAULT_HEIGHT_POPUP 400

struct Position {
  int x, y;
};

struct Geometry {
  int width, height;
};

struct Color {
  uint8_t r, g, b;
  float alpha;
};

#endif
