#ifndef UI_PANEL_SDL3_LUA_POPUP_MENU
#define UI_PANEL_SDL3_LUA_POPUP_MENU

#include "button.hpp"
#include "utils.hpp"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <memory>
#include <vector>

using WindowPtr = std::shared_ptr<SDL_Window>;
using RendererPtr =
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;

/*
 * @class PopMenu
 *
 * @brief Class to represent a popup menu window
 */
class PopupMenu {
private:
  const int max_height; ///< Const to represent the max height of the menu
  const int width;      ///< Const with the width of the window
  const int button_height;
  int current_height; ///< Variable to keep the current menu height
  bool pre_rendered =
      false; ///< Variable to avoid recalculate buttons positions

  std::shared_ptr<TTF_Font> loaded_font; ///< Font of the sdl

  /*
   * @brief Calculate the current height of the window using the button
   * height
   */
  void calculate_current_height();

  /*
   * @brief Calculate the buttons position on window using the current height
   *
   * @throw Throw the std::runtime_error if the window don't have buttons
   */
  void calculate_buttons_position();

  void generate_buttons_texture();

  void render_buttons(const SDL_Color &bg_color);

public:
  /*
   * @brief Vector with all buttons
   */
  std::vector<std::unique_ptr<Button>> buttons;

  /*
   * @brief Struct with the window position
   */
  Position menu_position;

  /*
   * @brief Smart pointer to represent the renderer
   */
  RendererPtr renderer;

  /*
   * @brief Smart pointer to represente the current window
   */
  WindowPtr current_window = nullptr;

  /*
   * @brief Weak reference to represent the parent_window
   */
  std::weak_ptr<PopupMenu> parent_window;

  /*
   * @brief Add a button to popup
   *
   * @param label Label to show on button
   * @param text_color Color of the label's text
   * @param function Name of the lua function of the button
   *
   * @return Return true if was success, else, return false
   */
  bool add_button(std::string label, SDL_Color text_color,
                  std::string function);

  /*
   * @brief Render all elements of the popup
   *
   * @return Return true if was success, else, return false
   */
  bool render(SDL_Color bg_color = {0, 0, 0, 255});

  /*
   * @brief Constructor from PopupMenu.
   *
   * @param menu_pos Position of the popup.
   * @param width Width of the popup.
   * @param font Font to show buttos label
   * @param max_height Max height of the popup.
   * @param parent_window Smart pointer to the parent popup, if it is the
   * original popup the pointer is nullptr.
   * @param button_height Height of each button, if don't passed any button.
   * height, then default height is choiced then use nullptr.
   *
   * @throw Throw the std::runtime_error if the window already exists.
   * @throw Throw the std::runtime_error if the window can't be created.
   * @throw Throw the std::runtime_error if the renderer can't be created.
   */
  PopupMenu(Position menu_pos, int width, std::shared_ptr<TTF_Font> font,
            int max_height = DEFAULT_HEIGHT_POPUP, int offset_x = 0,
            int offset_y = 0, std::shared_ptr<PopupMenu> parent_popup = nullptr,
            int button_height = DEFAULT_BUTTON_HEIGHT);

  /*
   * @brief Destructor from PopupMenu
   */
  ~PopupMenu();
};

#endif
