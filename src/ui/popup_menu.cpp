#include "popup_menu.hpp"
#include "button.hpp"
#include "utils.hpp"

#include <SDL3/SDL.h>
#include <iostream>
#include <memory>
#include <string>

bool PopupMenu::create_window(int offset_x, int offset_y) {

  // if the function already used
  if (this->current_window != nullptr) {
    std::cerr << "Erro: Window already created" << std::endl;
    return false;
  }

  if (this->parent_window == nullptr) {
    this->current_window =
        SDL_CreateWindow(APP_NAME, this->default_width, this->max_height,
                         SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALWAYS_ON_TOP);
  } else {
    this->current_window =
        SDL_CreatePopupWindow(this->parent_window, offset_x, offset_y,
                              this->default_width, this->max_height,
                              SDL_WINDOW_BORDERLESS | SDL_WINDOW_POPUP_MENU |
                                  SDL_WINDOW_ALWAYS_ON_TOP);
  }

  if (!this->current_window) {
    std::cerr << "Erro: Erro to create a Menu window" << std::endl;
    return false;
  }

  SDL_CreateRenderer(this->current_window, nullptr);
  if (!this->renderer) {
    SDL_DestroyWindow(this->current_window);

    std::cerr << "Erro: Erro to create a Menu render" << std::endl;
    return false;
  }

  return true;
}

bool PopupMenu::add_button(std::string label, Color font_color,
                           std::string function) {
  auto btn = std::make_shared<Button>(new Button(label, font_color, function));

  if (!btn) {
    std::cerr << "Erro: Erro to create a Button" << std::endl;
    return false;
  }

  buttons.push_back(btn);

  return true;
}

bool PopupMenu::render() {
  if (!this->current_window || !this->renderer)
    return false;

  return true;
}

PopupMenu::PopupMenu(Position menu_pos, SDL_Window *parent_window, int width,
                     int max_height)
    : menu_position(menu_pos), parent_window(parent_window),
      default_width(width), max_height(max_height) {}

PopupMenu::~PopupMenu() {
  this->buttons.clear();

  if (!this->current_window)
    SDL_DestroyWindow(this->current_window);

  if (!this->renderer)
    SDL_DestroyRenderer(this->renderer);
}
