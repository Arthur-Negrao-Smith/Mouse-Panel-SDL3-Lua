#include "button.hpp"
#include "utils.hpp"

#include <SDL3/SDL.h>

Button::Button(std::string label, SDL_Color font_color, std::string function)
    : label(label), font_color(font_color), function(function) {}

bool Button::is_focused(const Position &mouse_position) {
  if (this->rect.x <= mouse_position.x &&
      mouse_position.x <= this->rect.x + this->rect.w) {
    if (this->rect.y <= mouse_position.y &&
        mouse_position.y <= this->rect.y + this->rect.h) {
      return true;
    }
  }

  return false;
}
