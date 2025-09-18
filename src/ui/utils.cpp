#include "utils.hpp"

#include <SDL3/SDL.h>
#include <cstdint>
#include <sstream>
#include <stdexcept>
#include <string>

SDL_Color ColorUtils::hex_to_color(const std::string &hex) {
  // if isn't "#RRGGBB" or "#RRGGBBAA"
  if (hex.size() != 7 && hex.size() != 9) {
    throw std::invalid_argument(
        "Wrong format of the color. Use #RRGGBB or #RRGGBBAA");
  }

  if (hex[0] != '#') {
    throw std::invalid_argument("Color must have the '#' in first character");
  }

  // lambda function
  auto hex_to_byte = [](const std::string &str) -> uint8_t {
    return static_cast<uint8_t>(std::stoi(str, nullptr, 16));
  };

  auto r = hex_to_byte(hex.substr(1, 2));
  auto g = hex_to_byte(hex.substr(3, 2));
  auto b = hex_to_byte(hex.substr(5, 2));
  uint8_t alpha = 255; // default value

  if (hex.size() == 9)
    alpha = hex_to_byte(hex.substr(7, 2));

  return {r, g, b, alpha};
}

std::string ColorUtils::color_to_hex(const SDL_Color &color) {
  std::stringstream temp_color;
  temp_color << '#' << color.r << color.g << color.b << color.a;

  return temp_color.str();
}
