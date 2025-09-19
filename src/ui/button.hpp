#ifndef BUTTON_PANEL_SDL3_LUA
#define BUTTON_PANEL_SDL3_LUA

#include <SDL3/SDL.h>
#include <string>

/*
 * @struct Button
 * @brief Struct to represent a button menu
 */
struct Button {
  std::string label;    ///< Label to show on button
  SDL_Color font_color; ///< Font color of the label
  std::string function; ///< Lua function
  SDL_FRect rect;       ///< Rect to keep dimensions and position

  /*
   * @brief Add a button to popup
   *
   * @param label Label to show on button
   * @param text_color Color of the label's text
   * @param function Name of the lua function of the button
   */
  Button(std::string label, SDL_Color text_color, std::string function);
};

#endif
