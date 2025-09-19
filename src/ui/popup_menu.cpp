#include "popup_menu.hpp"
#include "button.hpp"
#include "utils.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_ttf/SDL_ttf.h>
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

  this->current_height = this->buttons.size() * this->button_height;
  SDL_SetWindowSize(this->current_window.get(), this->width,
                    this->current_height);

  // calculate the buttons positions
  Position current_position{0, 0};
  for (const auto &btn : this->buttons) {
    btn->rect.x = current_position.x;
    btn->rect.y = current_position.y;
    btn->rect.w = this->width;
    btn->rect.h = this->button_height;

    current_position.y += button_height;
  }
}

void PopupMenu::generate_buttons_texture() {
  for (const auto &btn : this->buttons) {

    // Create a surface to text
    std::unique_ptr<SDL_Surface, decltype(&SDL_DestroySurface)> text_surface(
        TTF_RenderText_Blended(this->loaded_font.get(), btn->label.c_str(), 0,
                               btn->font_color),
        &SDL_DestroySurface);
    if (!text_surface)
      throw std::runtime_error("Erro to create a text surface to button");

    // Create a texture to text
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> text_texture(
        SDL_CreateTextureFromSurface(this->renderer.get(), text_surface.get()),
        &SDL_DestroyTexture);
    if (!text_texture) {
      throw std::runtime_error("Erro to create a text texture to button");
    }

    // get the size of the texture
    SDL_GetTextureSize(text_texture.get(), &(btn->texture_rect.w),
                       &(btn->texture_rect.h));

    // to centralize the text
    const float padding = 10.0f;

    btn->texture_rect.x = btn->rect.x + padding;
    btn->texture_rect.y =
        btn->rect.y + (btn->rect.h / 2.0f) - (btn->texture_rect.h / 2.0f);

    btn->texture = std::move(text_texture);
    // customize the text shape
    if (!SDL_SetTextureScaleMode(btn->texture.get(), SDL_SCALEMODE_LINEAR))
      throw std::runtime_error("Erro to scale the texture of label");
  }
}

bool PopupMenu::add_button(std::string label, SDL_Color text_color,
                           std::string function) {
  auto btn = std::make_unique<Button>(label, text_color, function);

  if (!btn) {
    std::cerr << "Erro: Erro to create a Button" << std::endl;
    return false;
  }

  // to recalculate the buttons positions
  this->pre_rendered = false;

  buttons.push_back(std::move(btn));

  return true;
}

void PopupMenu::render_buttons(const SDL_Color &bg_color) {
  // Fill the background of the button
  SDL_SetRenderDrawColor(this->renderer.get(), bg_color.r, bg_color.g,
                         bg_color.b, bg_color.a);

  // Cleanup screen
  SDL_RenderClear(this->renderer.get());

  for (const auto &btn : this->buttons) {

    // Paint button
    SDL_RenderFillRect(this->renderer.get(), &(btn->rect));

    // Paint label of the button
    SDL_RenderTexture(this->renderer.get(), btn->texture.get(), nullptr,
                      &(btn->texture_rect));

    // Draw a line to separete buttons
    SDL_SetRenderDrawColor(this->renderer.get(), 255, 255, 255, 255);
    SDL_RenderLine(this->renderer.get(), btn->rect.x,
                   btn->rect.y + btn->rect.h - 1, btn->rect.x + btn->rect.w,
                   btn->rect.y + btn->rect.h - 1);

    // Return to original color
    SDL_SetRenderDrawColor(this->renderer.get(), bg_color.r, bg_color.g,
                           bg_color.b, bg_color.a);
  }

  // Show the screen updated
  SDL_RenderPresent(this->renderer.get());
}

bool PopupMenu::render(SDL_Color bg_color) {
  if (!this->current_window || !this->renderer) {
    std::cerr << "Erro: Window or Renderer don't exist." << std::endl;
    return false;
  }

  if (!this->pre_rendered) {
    calculate_current_height();

    try {
      calculate_buttons_position();
      generate_buttons_texture();

    } catch (std::runtime_error NoButtonsError) {
      std::cerr << "Erro: Don't have buttons to calculate they positions."
                << std::endl;
      return false;
    }

    this->pre_rendered = true;
  }

  render_buttons(bg_color);

  return true;
}

PopupMenu::PopupMenu(Position menu_pos, int width,
                     std::shared_ptr<TTF_Font> font, int max_height,
                     int offset_x, int offset_y,
                     std::shared_ptr<PopupMenu> parent_popup, int button_height)
    : menu_position(menu_pos), width(width), loaded_font(font),
      max_height(max_height), parent_window(parent_popup),
      button_height(button_height),
      // init the renderer like a nullptr
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

PopupMenu::~PopupMenu() = default;
