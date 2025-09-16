#include "button.hpp"
#include "popup_menu.hpp"
#include "utils.hpp"
#include <SDL3/SDL.h>
#include <cstdlib>
#include <string>

PopupMenu::PopupMenu(Position menu_pos, SDL_Window *parent_window,
                     unsigned width, unsigned max_height)
    : menu_position(menu_pos), parent_window(parent_window),
      default_width(width), max_height(max_height) {
  if (this->parent_window == nullptr) {
    SDL_CreateWindow(APP_NAME, this->default_width, this->max_height,
                     SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALWAYS_ON_TOP);
  } else {
    SDL_CreatePopupWindow(this->parent_window, menu_pos.x, menu_pos.y,
                          this->default_width, this->max_height,
                          SDL_WINDOW_BORDERLESS | SDL_WINDOW_POPUP_MENU |
                              SDL_WINDOW_ALWAYS_ON_TOP);
  }

  if (!this->current_window) {
    std::cerr << "Erro: Erro to create a Menu window" << std::endl;
    exit(EXIT_FAILURE);
  }

  SDL_CreateRenderer(this->current_window, nullptr);
  if (!this->renderer) {
    std::cerr << "Erro: Erro to create a Menu render" << std::endl;
    exit(EXIT_FAILURE);
  }
}

PopupMenu::~PopupMenu() {
  for (auto &btn : this->buttons)
    delete btn;

  if (!this->current_window)
    SDL_DestroyWindow(this->current_window);
  if (!this->renderer)
    SDL_DestroyRenderer(this->renderer);
}
