#include "vm.hpp"
#include "graphics.hpp"

// Fonction d'initialisation qui est appelée en premier
void executeProgram(ProgramState &ps) {
  ps.ic = 0;

  if (ps.allInstructions[0]->type != GRAPHICS_INIT) {
    cout << "Lancement du programme en mode console" << endl;

    while (ps.ic < ps.allInstructions.size()) {
      executeNextInstruction(ps);
    }

    exit(0);
  }

  else {
    cout << "Lancement du programme en mode graphique" << endl;

	  executeGraphicsContext(ps);
  }
}