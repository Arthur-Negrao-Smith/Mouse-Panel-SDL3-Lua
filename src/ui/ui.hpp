#ifndef UI_PANEL_SDL3_LUA
#define UI_PANEL_SDL3_LUA

#include "utils.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <string>
#include <vector>

#define APP_NAME "Mouse Panel"
#define DEFAULT_WIDTH_POPUP 200
#define DEFAULT_HEIGHT_POPUP 400

typedef struct {
  std::string label;
  Color font_color;
  std::string funtion;
} Button;

typedef struct {
  SDL_Window *window;
  SDL_Renderer *render;
  std::vector<Button> buttons;
} PopupMenu;

class UIManager {
private:
  std::vector<PopupMenu> popups;
  Geometry get_resolution();
  SDL_Window *window;
  SDL_Renderer *render;

public:
  /**
   * @brief Add a top popup menu
   * * If the first menu is it, then the menu will be a owner of main window
   */
  void push_popup(PopupMenu new_popup);

  /**
   * @brief Add a button to top popup menu
   */
  void add_menu_button();

  /**
   * @brief Remove the top popup menu
   */
  void pop_popup();

  UIManager();
  ~UIManager();
};

#endif
