/*
File with util structures
*/

#ifndef UTILS_PAANEL_SDL3_LUA
#define UTILS_PAANEL_SDL3_LUA

#include <cstdint>
#include <string>

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

/*
 * @struct Position
 *
 * @brief Struct to keep a position
 */
struct Position {
  int x; ///< X coordinate
  int y; ///< Y coordinate
};

/*
 * @struct Geometry
 *
 * @brief Geometry to keep sizes
 */
struct Geometry {
  int width;  ///< width of the element
  int height; ///< height of the element
};

/*
 * @struct Color
 *
 * @brief Struct to keep colors
 */
struct Color {
  uint8_t r;     ///< Red number
  uint8_t g;     ///< Green number
  uint8_t b;     ///< Blue number
  uint8_t alpha; ///< Alpha number
};

/*
 * @class ColorUtils
 *
 * @brief Utilities to use colors
 */
class ColorUtils {
public:
  /*
   * @brief Convert hexadecimal values to color
   *
   * @param hex String with hexadecimal to convert
   *
   * @return The respective Color
   *
   * @throw std::invalid_argument if size of hexadecimal is invalid
   * @throw std::invalid_argument if the first element isn't "#"
   * @throw std::out_of_range if number is to big hexadecimal
   */
  static Color fromHex(const std::string &hex);
};

#endif
