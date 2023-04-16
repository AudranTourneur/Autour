#include "ProgramState.hpp"
#include "structs.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <thread>
#include <optional>

using namespace std;

// La majorité de la logique réside dans cette fonction
// La logique d'éxécution est triviale pour la plupart des instructions
// Les instructions de type graphique sont gérés spécialement par le fichier graphics.cpp
opcode executeNextInstruction(ProgramState &ps, bool automaticTermination) {
  auto &ic = ps.ic;
  auto &allInstructions = ps.allInstructions;
  auto &variablesTable = ps.variablesTable;
  auto &memoryStack = ps.memoryStack;

  if (ps.ic < allInstructions.size()) {
    Instruction *instruction = allInstructions[ic];

    if (instruction->type == LOAD_LITERAL) { // Chargement d'un nombre ou d'une chaîne de caractères
      if (instruction->valueStr != "") {
        ps.memoryStack.push(instruction->valueStr);
      } else {
        ps.memoryStack.push(instruction->valueNum);
      }
      ps.ic++;
    } else if (instruction->type == LOAD_VARIABLE) { // Chargement d'une variable
      ps.memoryStack.push(variablesTable[instruction->valueStr]);
      ps.ic++;
    } else if (instruction->type == LOAD_LIST) { // Chargement d'une liste
      std::vector<VariableWrapper> list;

      int i = 0;
      // Récupérer les éléments de la liste qui sont sur la pile
      while (i < instruction->valueNum) {
        VariableWrapper a = ps.memoryStack.top();
        ps.memoryStack.pop();

        list.push_back(a);

        i++;
      }

      // Inverser la liste pour avoir les éléments dans le bon ordre
      std::reverse(list.begin(), list.end());

      VariableWrapper listWrapper = new VariableWrapper(list);

      ps.memoryStack.push(list);
      ps.ic++;

    } else if (instruction->type == LOAD_LIST_ITEM) { // Charge le ième élément d'une liste
      VariableWrapper index = ps.memoryStack.top();
      ps.memoryStack.pop();
      VariableWrapper list = ps.memoryStack.top();
      ps.memoryStack.pop();

      ps.memoryStack.push(list[index.valueNumber]);

      ps.ic++;
    } else if (instruction->type == STORE_LIST) { // Stocke une valeur dans une liste
      VariableWrapper value = ps.memoryStack.top(); // Chargement de la valeur
      ps.memoryStack.pop();
      VariableWrapper index = ps.memoryStack.top(); // Chargement de l'index souhaité
      ps.memoryStack.pop();

      string variableName = instruction->valueStr;
      auto &list = variablesTable[variableName].valueList;

      // Élargir la liste si nécessaire
      if (index.valueNumber >= list->size()) {
        list->resize(index.valueNumber + 1);
      }

      list->operator[](index.valueNumber) = value;

      ps.ic++;
    } else if (instruction->type == ADD) { // Addition ou concaténation
      VariableWrapper a = ps.memoryStack.top();
      ps.memoryStack.pop();
      VariableWrapper b = ps.memoryStack.top();
      ps.memoryStack.pop();
      auto res = b + a;
      ps.memoryStack.push(res);
      ps.ic++;
    } else if (instruction->type == SUB) { // Soustraction
      VariableWrapper a = memoryStack.top();
      memoryStack.pop();
      VariableWrapper b = memoryStack.top();
      memoryStack.pop();
      memoryStack.push(b - a);
      ic++;
    } else if (instruction->type == MUL) { // Multiplication
      VariableWrapper a = memoryStack.top();
      memoryStack.pop();
      VariableWrapper b = memoryStack.top();
      memoryStack.pop();
      memoryStack.push(b * a);
      ic++;
    } else if (instruction->type == DIV) { // Division
      VariableWrapper a = memoryStack.top();
      memoryStack.pop();
      VariableWrapper b = memoryStack.top();
      memoryStack.pop();
      memoryStack.push(b / a);
      ic++;
    } 
    else if (instruction->type == MOD) { // Modulo
      VariableWrapper a = memoryStack.top();
      memoryStack.pop();
      VariableWrapper b = memoryStack.top();
      memoryStack.pop();

      memoryStack.push(b % a);
    
      ic++;
    } 
    else if (instruction->type == STORE) { // Stockage d'une valeur
      VariableWrapper a = memoryStack.top();
      memoryStack.pop();
      variablesTable[instruction->valueStr] = a;

      ic++;
    } else if (instruction->type == PRINT) { // Affichage d'une valeur
      VariableWrapper a = memoryStack.top();
      memoryStack.pop();
      cout << "SORTIE\t>>\t " << a << endl;
      ic++;

    } else if (instruction->type == INPUT) { // Entrée d'une variable
      double a;
      cout << "ENTRÉE \t<<\t ";
      cin >> a;
      variablesTable[instruction->valueStr] = a;
      ic++;
    } else if (instruction->type == NOP) { // Ne fait rien
      ic++;
    } else if (instruction->type == SLEEP) { // Pause
      this_thread::sleep_for(chrono::milliseconds((int)instruction->valueNum));
      ic++;
    } else if (instruction->type == JUMP_IF_FALSE) { // Saut conditionnel
      VariableWrapper a = memoryStack.top();
      memoryStack.pop();
      if (!a.getTruthiness()) {
        if (instruction->valueStr != "") {
          ic = ps.labels[instruction->valueStr];
        } else {
          ic = instruction->valueNum;
        }
      } else {
        ic++;
      }
    } else if (instruction->type == JUMP) { // Saut inconditionnel
      if (instruction->valueStr != "") {
        ic = ps.labels[instruction->valueStr];
      } else {
        ic = instruction->valueNum;
      }
    } else if (instruction->type == CMP_EQ) { // Comparaison d'égalité
      VariableWrapper a = memoryStack.top();
      memoryStack.pop();
      VariableWrapper b = memoryStack.top();
      memoryStack.pop();

      memoryStack.push(b == a);
      ic++;
    } else if (instruction->type == CMP_GT) { // Comparaison de supériorité
      VariableWrapper a = memoryStack.top();
      memoryStack.pop();
      VariableWrapper b = memoryStack.top();
      memoryStack.pop();

      memoryStack.push(b > a);
      ic++;
    } else if (instruction->type == CMP_LT) { // Comparaison d'infériorité
      VariableWrapper a = memoryStack.top();
      memoryStack.pop();
      VariableWrapper b = memoryStack.top();
      memoryStack.pop();

      memoryStack.push(b < a);
      ic++;
    } else if (instruction->type == CMP_GTE) { // Comparaison de supériorité ou d'égalité
      VariableWrapper a = memoryStack.top();
      memoryStack.pop();
      VariableWrapper b = memoryStack.top();
      memoryStack.pop();

      memoryStack.push(b >= a);
      ic++;
    } else if (instruction->type == CMP_LTE) { // Comparaison d'infériorité ou d'égalité
      VariableWrapper a = memoryStack.top();
      memoryStack.pop();
      VariableWrapper b = memoryStack.top();
      memoryStack.pop();

      memoryStack.push(b <= a);
      ic++;
    } else if (instruction->type == CMP_NEQ) { // Comparaison de différence
      VariableWrapper a = memoryStack.top();
      memoryStack.pop();
      VariableWrapper b = memoryStack.top();
      memoryStack.pop();

      memoryStack.push(b != a);
      ic++;
    } else if (instruction->type == NEG) { // Négation
      VariableWrapper a = memoryStack.top();
      memoryStack.pop();
      memoryStack.push(-a);
      ic++;
    } else if (instruction->type == MATH_SQRT) { // Racine carrée
      VariableWrapper a = memoryStack.top();
      memoryStack.pop();
      memoryStack.push(sqrt(a.valueNumber));
      ic++;
    } else if (instruction->type == GRAPHICS_INIT) { // Initialisation de la fenêtre graphique
      ic++;
    } else if (instruction->type == COLOR_PIXEL) { // Coloration d'un pixel (utilise 5 valeurs sur la pile)
       VariableWrapper blue = memoryStack.top();
       memoryStack.pop();
       VariableWrapper green = memoryStack.top();
       memoryStack.pop();
       VariableWrapper red = memoryStack.top();
       memoryStack.pop();

        VariableWrapper y = memoryStack.top();
        memoryStack.pop();
        VariableWrapper x = memoryStack.top();
        memoryStack.pop();

      ps.pixels[(int) x.valueNumber][(int) y.valueNumber] = make_tuple(red.valueNumber, green.valueNumber, blue.valueNumber);
      ic++;
    } 
    else if (instruction->type == GRAPHICS_UPDATE) { // Mise à jour de la fenêtre graphique
      ic++;
    }
    else if (instruction->type == CALL) { // Appel d'une procédure
      if (instruction->valueStr != "") {

        ps.callStack.push(ic);

        ic = ps.labels[instruction->valueStr];

      } else {
        exit(1);
      }
    }
    else if (instruction->type == RETURN) { // Retour d'une procédure
      if (ps.callStack.empty()) {
        if (automaticTermination)
          exit(0);
        else
          return HALT;
      }

      ic = ps.callStack.top()+1;
      ps.callStack.pop();
    }
    else if (instruction->type == LOGIC_AND) { // Opérateur ET logique
      VariableWrapper a = memoryStack.top();
      memoryStack.pop();
      VariableWrapper b = memoryStack.top();
      memoryStack.pop();

      memoryStack.push(b && a);
      ic++;
    }
    else if (instruction->type == LOGIC_OR) { // Opérateur OU logique
      VariableWrapper a = memoryStack.top();
      memoryStack.pop();
      VariableWrapper b = memoryStack.top();
      memoryStack.pop();

      memoryStack.push(b || a);
      ic++;
    }
    else { // Instruction inconnue, n'est pas censé arriver
      cout << "Unknown instruction: " << instruction->type << endl;
      ic++;
      exit(1);
    }

    return instruction->type; // renvoie le type de l'instruction exécutée
  }
  return HALT;
}