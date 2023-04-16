#include "ProgramState.hpp"
#include "structs.hpp"
#include "vm.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <iostream>

using namespace std;

// Gestion de la fenêtre graphique
void handleGraphicsUpdate(ProgramState &ps, SDL_Renderer *rend, int width,
                          int height) {
  SDL_RenderClear(rend);

  const int numberOfSquares = 50;
  const int squareSize = width / numberOfSquares;

  // Affichage de la matrice de pixels 50x50 depuis la mémoire programme spéciale
  for (int i = 0; i < numberOfSquares; i++) {
    for (int j = 0; j < numberOfSquares; j++) {
      SDL_Rect rect = {i * squareSize, j * squareSize, squareSize, squareSize};

      SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

      std::tuple<int, int, int> color = ps.pixels[i][j];
      SDL_SetRenderDrawColor(rend, std::get<0>(color), std::get<1>(color),
                             std::get<2>(color), 255);

      SDL_RenderFillRect(rend, &rect);
    }
  }

  SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);

  SDL_RenderPresent(rend);

  SDL_Delay(1000 / 60); // 60 fps
}

void executeGraphicsContext(ProgramState &ps) {

  // returns zero on success else non-zero
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    printf("error initializing SDL: %s\n", SDL_GetError());
  }

  const int width = 700;
  const int height = 700;

  SDL_Window *win = SDL_CreateWindow(
      "Langage AUTOUR - Mode graphique", // creates a window
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

  // Accélération matérielle
  Uint32 render_flags = SDL_RENDERER_ACCELERATED;

  // Création du renderer
  SDL_Renderer *rend = SDL_CreateRenderer(win, -1, render_flags);

  int close = 0;

  // Boucle d'animation principale
  while (!close) {
    SDL_Event event;

    // Gestion des évènements (fermeture de la fenêtre)
    while (SDL_PollEvent(&event)) {
      switch (event.type) {

      case SDL_QUIT:
        cout << "Arrêt du programme par l'utilisateur" << endl;
        close = 1;
        break;
      }
    }

    // La machine virtuelle est exécutée jusqu'à ce qu'elle rencontre une
    // instruction GRAPHICS_UPDATE ou HALT
    opcode lastOpcode = NOP;
    while (lastOpcode != GRAPHICS_UPDATE) {
      lastOpcode = executeNextInstruction(ps, false);
      if (lastOpcode == HALT || lastOpcode == NOP) {
        cout << "Le programme est terminé" << endl;
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        exit(0);
      }
    }
    handleGraphicsUpdate(ps, rend, width, height);
  }

  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(win);
  SDL_Quit();
}
