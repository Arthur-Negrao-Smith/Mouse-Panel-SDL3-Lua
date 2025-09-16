#ifndef BUTTON_PANEL_SDL3_LUA
#define BUTTON_PANEL_SDL3_LUA

#include "utils.hpp"

#include <SDL3/SDL.h>
#include <string>

/*
 * @struct Button
 * @brief Struct to represent a button menu
 */
struct Button {
  std::string label;    ///< Label to show on button
  Color font_color;     ///< Font color of the label
  std::string function; ///< Lua function
  SDL_Rect rect;        ///< Rect to keep dimensions and position

  /*
   * @brief Add a button to popup
   *
   * @param label Label to show on button
   * @param font_color Color of the label's font
   * @param functino Name of the lua function of the button
   */
  Button(std::string label, Color font_color, std::string function);
};

#endif
