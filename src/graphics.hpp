#pragma once

#include "ProgramState.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

void handleGraphicsUpdate(ProgramState &ps, SDL_Renderer *rend, int width,
                          int height);

void executeGraphicsContext(ProgramState &ps);
