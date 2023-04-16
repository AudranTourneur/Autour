#pragma once

#include "VariableWrapper.hpp"
#include "structs.hpp"

#include <array>
#include <map>
#include <stack>
#include <string>
#include <tuple>
#include <vector>

/*
  Représente l'état du programme à un instant donné
*/

class ProgramState {
public:
  int ic = 0; // instruction en cours d'éxécution
  std::vector<Instruction *> allInstructions; // vecteur d'instructions

  std::map<std::string, VariableWrapper> variablesTable; // table des variables de type arbitraire
  std::map<std::string, int> labels; // nom des labels vers l'instruction correspondante

  std::stack<VariableWrapper> memoryStack; // pile de la mémoire

  std::stack<int> encouteredLists; // Les identifiants des listes en train d'être parsés

  std::stack<int> callStack; // pile d'appels pour les procédures

  std::array<std::array<std::tuple<int, int, int>, 50>, 50> pixels;  // écran pour le mode graphique, taille 50x50, chaque pixel est un tuple (r, g, b)

  // ajout d'instruction avec les opérandes en paramètre
  void addInstruction(opcode type = NOP, double numValue = 0,
                      const string &stringValue = "");

  // renvoie un identifiant unique pour les listes et les structures de contrôle
  int getUniqueInternalId();
};