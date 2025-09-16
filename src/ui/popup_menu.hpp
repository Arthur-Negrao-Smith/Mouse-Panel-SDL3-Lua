#ifndef UI_PANEL_SDL3_LUA_POPUP_MENU
#define UI_PANEL_SDL3_LUA_POPUP_MENU

#include "button.hpp"
#include "utils.hpp"

#include <SDL3/SDL.h>
#include <memory>
#include <vector>

class PopupMenu {
private:
  const unsigned max_height;
  const unsigned default_width;

public:
  std::vector<std::shared_ptr<Button>> buttons;
  Position menu_position;
  SDL_Renderer *renderer;
  SDL_Window *current_window = nullptr;
  SDL_Window *parent_window;

  bool create_window(int offset_x, int offset_y);
  bool add_button(Button new_button);
  PopupMenu(Position menu_pos, SDL_Window *parent_window, int width,
            int max_height);
  ~PopupMenu();
};

#endif
