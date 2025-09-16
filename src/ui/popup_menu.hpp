#ifndef UI_PANEL_SDL3_LUA_POPUP_MENU
#define UI_PANEL_SDL3_LUA_POPUP_MENU

#include "button.hpp"
#include "utils.hpp"

#include <SDL3/SDL.h>
#include <memory>
#include <vector>

class PopupMenu {
private:
  const int max_height;
  const int default_width;
  int current_height;

  void calculate_buttons_position();
  void calculate_current_height();

public:
  std::vector<std::shared_ptr<Button>> buttons;
  Position menu_position;
  SDL_Renderer *renderer;
  SDL_Window *current_window = nullptr;
  SDL_Window *parent_window;

  /*
   * @brief Create a window to popup
   *
   * @param offset_x Offset of X axle from original popup
   * @param offset_y Offset of Y axle from original popup
   *
   * @return Return true if was success, else, return false
   */
  bool create_window(int offset_x, int offset_y);

  /*
   * @brief Add a button to popup
   *
   * @param label Label to show on button
   * @param font_color Color of the label's font
   * @param functino Name of the lua function of the button
   *
   * @return Return true if was success, else, return false
   */
  bool add_button(std::string label, Color font_color, std::string function);

  /*
   * @brief Render all elements of the popup
   *
   * @return Return true if was success, else, return false
   */
  bool render();

  /*
   * @brief Constructor from PopupMenu
   *
   * @param menu_pos Position of the popup
   * @param width Width of the popup
   * @param max_height Max height of the popup
   * @param parent_window Pointer to original popup, if it is the original popup
   * then use nullptr
   */
  PopupMenu(Position menu_pos, int width, int max_height,
            SDL_Window *parent_window = nullptr);

  /*
   * @brief Destructor from PopupMenu
   */
  ~PopupMenu();
};

#endif
