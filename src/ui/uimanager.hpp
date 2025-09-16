#ifndef UIMANAGER_PANEL_SDL3_LUA
#define UIMANAGER_PANEL_SDL3_LUA

#include "popup_menu.hpp"
#include "utils.hpp"

#include <SDL3/SDL.h>

#define DEFAULT_WIDTH_POPUP 200
#define DEFAULT_HEIGHT_POPUP 400

class UIManager {
private:
  /// Vector with popup menus
  std::vector<PopupMenu *> popups;

  /*
   * @brief Get the screen resolution
   */
  Geometry get_resolution();

  const Color menu_bg;
  const Color btn_hover;
  const Color btn_focused;
  const Color btn_default;

public:
  /**
   * @brief Add a top popup menu
   * * If the first menu is it, then the menu will be a owner of main window
   */
  void push_popup(PopupMenu *new_popup);

  /**
   * @brief Remove the top popup menu
   */
  void pop_popup();

  void render();

  /**
   * @brief Constructor from UIManager
   */
  UIManager(Color menu_bg, Color btn_hover, Color btn_focused,
            Color btn_default);

  /**
   * @brief Destructor from UIManager
   */
  ~UIManager();
};

#endif
