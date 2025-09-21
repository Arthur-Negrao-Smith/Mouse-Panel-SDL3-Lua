#ifndef UIMANAGER_PANEL_SDL3_LUA
#define UIMANAGER_PANEL_SDL3_LUA

#include "popup_menu.hpp"
#include "utils.hpp"

#include <SDL3/SDL.h>
#include <memory>
#include <string>

class UIManager {
private:
  /// Vector with popup menus
  std::vector<std::shared_ptr<PopupMenu>> popups;

  /*
   * @brief Get the screen resolution
   */
  Geometry get_resolution();

  const std::string btn_hover_color;
  const std::string btn_focused_color;
  const std::string btn_default_color;

public:
  /**
   * @brief Add a top popup menu
   * * If the first menu is it, then the menu will be a owner of main window
   */
  void push_popup(std::shared_ptr<PopupMenu> new_popup);

  /**
   * @brief Remove the top popup menu
   */
  void pop_popup();

  void render();

  /**
   * @brief Constructor from UIManager
   */
  UIManager(const std::string &btn_default_color,
            const std::string &btn_hover_color,
            const std::string &btn_focused_color);

  /**
   * @brief Destructor from UIManager
   */
  ~UIManager();
};

#endif
