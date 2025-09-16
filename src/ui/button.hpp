#ifndef BUTTON_PANEL_SDL3_LUA
#define BUTTON_PANEL_SDL3_LUA

#include "utils.hpp"

#include <SDL3/SDL.h>
#include <string>

class Button {
public:
  std::string label;
  Color font_color;
  std::string function;
  SDL_Rect rect;

  Button(std::string label, Color font_color, std::string function);
};

#endif
