#include "button.hpp"

#include <SDL3/SDL.h>

Button::Button(std::string label, SDL_Color font_color, std::string function)
    : label(label), font_color(font_color), function(function) {}
