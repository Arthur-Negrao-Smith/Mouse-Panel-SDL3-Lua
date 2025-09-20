/*
File with util structures
*/

#ifndef UTILS_PAANEL_SDL3_LUA
#define UTILS_PAANEL_SDL3_LUA

#include <SDL3/SDL.h>
#include <string>

/*
 * @brief Constant to define the app name
 */
#define APP_NAME "Mouse Panel"

/*
 * @brief Constant to define the default color
 */
#define DEFAULT_COLOR_TEXT "default"

/*
 * @brief Constant to define default button height
 */
#define DEFAULT_BUTTON_HEIGHT 30

#define DEFAULT_BUTTON_COLOR {40, 40, 40, 255}

#define DEFAULT_FOCUSED_BUTTON_COLOR {100, 100, 100, 255}

#define DEFAULT_CLICKED_BUTTON_COLOR {255, 255, 255, 255}

/*
 * @brief Constant to define default width of the popup menu
 */
#define DEFAULT_WIDTH_POPUP 200

/*
 * @brief Constante to define default height of the popup menu
 */
#define DEFAULT_HEIGHT_POPUP 400

/*
 * @brief Macro to keep default font
 */
#define DEFAULT_FONT_NAME "../src/Roboto-VariableFont_wdth,wght.ttf"

#define DEFAULT_FONT_SIZE 18

/*
 * @struct Position
 *
 * @brief Struct to keep a position
 */
struct Position {
  float x; ///< X coordinate
  float y; ///< Y coordinate
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
  static SDL_Color hex_to_color(const std::string &hex);

  /*
   * @brief Convert Color to string
   *
   * @param color Color to convert to a string
   *
   * @return The respective string
   */
  static std::string color_to_hex(const SDL_Color &color);
};

#endif
