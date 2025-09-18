#include "popup_menu.hpp"
#include "button.hpp"
#include "utils.hpp"

#include <SDL3/SDL.h>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

void PopupMenu::calculate_current_height() {
  int temp_height = this->buttons.size() * this->button_height;

  // if the new height not overflowing
  if (temp_height < this->max_height)
    this->current_height = temp_height;
}

void PopupMenu::calculate_buttons_position() {
  if (this->buttons.size() == 0)
    throw std::runtime_error("No buttons in menu");

  // if buttons don't fit in the window
  if (this->buttons.size() * this->button_height > this->max_height) {
    int number_to_remove =
        this->buttons.size() -
        static_cast<int>(this->max_height / this->button_height);

    // remove overflowed buttons
    for (int i = 0; i < number_to_remove; i++)
      this->buttons.pop_back();
  }

  // calculate the buttons positions
  Position current_position{0, 0};
  for (auto btn : this->buttons) {
    btn->rect.x = current_position.x;
    btn->rect.y = current_position.y;

    current_position.y += button_height;
  }
}

bool PopupMenu::add_button(std::string label, Color font_color,
                           std::string function) {
  auto btn = std::make_shared<Button>(label, font_color, function);

  if (!btn) {
    std::cerr << "Erro: Erro to create a Button" << std::endl;
    return false;
  }

  // to recalculate the buttons positions
  this->pre_rendered = false;

  buttons.push_back(btn);

  return true;
}

bool PopupMenu::render() {
  if (!this->current_window || !this->renderer) {
    std::cerr << "Erro: Window or Renderer don't exist." << std::endl;
    return false;
  }

  if (!this->pre_rendered) {
    calculate_current_height();

    try {
      calculate_buttons_position();

    } catch (std::runtime_error NoButtonsError) {
      std::cerr << "Erro: Don't have buttons to calculate they positions."
                << std::endl;
      return false;
    }

    this->pre_rendered = true;
  }

  return true;
}

PopupMenu::PopupMenu(Position menu_pos, int width, int max_height, int offset_x,
                     int offset_y, std::shared_ptr<PopupMenu> parent_popup,
                     int button_height)
    : menu_position(menu_pos), width(width), max_height(max_height),
      parent_window(parent_popup), button_height(button_height),
      renderer(nullptr, &SDL_DestroyRenderer) {

  // if the function already used
  if (this->current_window != nullptr) {
    throw std::runtime_error("Window already created");
  }

  SDL_Window *temp_window;
  if (parent_popup == nullptr) {
    temp_window =
        SDL_CreateWindow(APP_NAME, this->width, this->max_height,
                         SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALWAYS_ON_TOP);
  } else {
    temp_window =
        SDL_CreatePopupWindow(parent_popup->current_window.get(), offset_x,
                              offset_y, this->width, this->max_height,
                              SDL_WINDOW_BORDERLESS | SDL_WINDOW_POPUP_MENU |
                                  SDL_WINDOW_ALWAYS_ON_TOP);
  }

  if (!temp_window) {
    throw std::runtime_error("Erro to create a Menu window");
  }
  this->current_window = WindowPtr(temp_window, &SDL_DestroyWindow);

  SDL_Renderer *temp_renderer =
      SDL_CreateRenderer(this->current_window.get(), nullptr);
  if (!temp_renderer) {
    throw std::runtime_error("Erro to create a Menu renderer");
  }
  this->renderer.reset(temp_renderer);
}

PopupMenu::~PopupMenu() { this->buttons.clear(); }
