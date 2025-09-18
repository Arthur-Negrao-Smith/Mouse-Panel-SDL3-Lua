#include "uimanager.hpp"
#include "popup_menu.hpp"
#include "utils.hpp"

#include <SDL3/SDL.h>
#include <cstdlib>
#include <iostream>
#include <ostream>

Geometry UIManager::get_resolution() {
  SDL_DisplayID displayID = SDL_GetPrimaryDisplay();
  const SDL_DisplayMode *display = SDL_GetCurrentDisplayMode(displayID);

  Geometry res;
  res.height = display->h;
  res.width = display->w;

  return res;
}

UIManager::UIManager(Color menu_bg, Color btn_hover, Color btn_focused,
                     Color btn_default)
    : menu_bg(menu_bg), btn_hover(btn_hover), btn_focused(btn_focused),
      btn_default(btn_default) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "Erro: Erro to iniate the SDL" << std::endl;
    exit(EXIT_FAILURE);
  }
}

UIManager::~UIManager() {
  this->popups.clear();
  SDL_Quit();
}

void UIManager::push_popup(std::shared_ptr<PopupMenu> new_popup) {
  this->popups.push_back(new_popup);
}

void UIManager::pop_popup() {
  if (!this->popups.empty())
    this->popups.pop_back();
}
