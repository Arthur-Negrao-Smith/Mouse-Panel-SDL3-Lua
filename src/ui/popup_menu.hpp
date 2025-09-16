#ifndef UI_PANEL_SDL3_LUA_POPUP_MENU
#define UI_PANEL_SDL3_LUA_POPUP_MENU

#include "button.hpp"
#include "utils.hpp"

#include <SDL3/SDL.h>
#include <string>
#include <vector>

class PopupMenu {
private:
  const unsigned max_height;
  const unsigned default_width;

public:
  std::vector<Button *> buttons;
  Position menu_position;
  SDL_Renderer *renderer;
  SDL_Window *current_window;
  SDL_Window *parent_window;

  void add_button(Button new_button);
  PopupMenu(Position menu_pos, SDL_Window *parent_window, unsigned width,
            unsigned max_height);
  ~PopupMenu();
};

Button *create_button(std::string label, Color font_color,
                      std::string function);

#endif
