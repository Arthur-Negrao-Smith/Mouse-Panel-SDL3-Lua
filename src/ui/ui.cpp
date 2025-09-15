#include "ui.hpp"
#include "utils.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
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

UIManager::UIManager() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "Erro: Erro to iniate the SDL" << std::endl;
    exit(EXIT_FAILURE);
  }

  this->window =
      SDL_CreateWindow(APP_NAME, DEFAULT_WIDTH_POPUP, DEFAULT_HEIGHT_POPUP,
                       SDL_WINDOW_BORDERLESS | SDL_WINDOW_POPUP_MENU);
  if (!this->window) {
    std::cerr << "Erro: Erro to iniate the Main Window" << std::endl;
    exit(EXIT_FAILURE);
  }

  this->render = SDL_CreateRenderer(this->window, nullptr);
  if (!this->render) {
    std::cerr << "Erro: Erro to iniate the Render" << std::endl;
    exit(EXIT_FAILURE);
  }
}

UIManager::~UIManager() {
  if (this->window)
    SDL_DestroyWindow(this->window);

  if (this->render)
    SDL_DestroyRenderer(this->render);

  SDL_Quit();
}

void UIManager::push_popup(PopupMenu new_popup) {
  // SDL_CreatePopupWindow
  // SDL_CreateRenderer
  this->popups.push_back(new_popup);
}

void UIManager::pop_popup() {
  PopupMenu current_popup = popups.back();

  if (current_popup.window)
    SDL_DestroyWindow(current_popup.window);

  if (current_popup.render)
    SDL_DestroyRenderer(current_popup.render);

  this->popups.pop_back();
}
