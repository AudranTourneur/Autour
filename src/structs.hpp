#pragma once

#include <string>

// Définition des types d'opcode
enum opcode {
    NOP, // Instruction vide
    LOAD_LITERAL, // Charge une valeur littérale
    LOAD_VARIABLE, // Charge une variable
    ADD, // Addition ou concaténation
    SUB, // Soustraction
    MUL, // Multiplication
    DIV, // Division
    MOD, // Modulo
    STORE, // Stocke une valeur dans une variable
    PRINT, // Affiche une valeur
    INPUT, // Demande une valeur à l'utilisateur
    CALL, // Appelle une fonction
    RETURN, // Retourne de la fonction
    HALT, // Arrête le programme
    SLEEP, // Met en pause le programme pour X millisecondes
    JUMP, // Saut à une instruction
    JUMP_IF_FALSE, // Saut à une instruction si la condition est fausse (dans la pile)
	CMP_EQ, // Opérateur de comparaison ==
	CMP_GT, // Opérateur de comparaison >
	CMP_GTE, // Opérateur de comparaison >=
	CMP_LT, // Opérateur de comparaison <
	CMP_LTE, // Opérateur de comparaison <=
	CMP_NEQ, // Opérateur de comparaison !=
    LOGIC_AND,  // Opérateur logique ET
    LOGIC_OR,  // Opérateur logique OU
    LOGIC_NOT, // Opérateur logique NON
    NEG, // Opérateur unaire de négation
    MATH_SQRT, // Racine carrée
    LOAD_LIST, // Charge une liste
    LOAD_LIST_ITEM, // Charge un élément d'une liste
    STORE_LIST, // Stocke une liste dans une variable
    GRAPHICS_INIT, // Initialise la fenêtre graphique
    COLOR_PIXEL, // Colorie un pixel
    GRAPHICS_UPDATE, // Met à jour la fenêtre graphique
};

std::string opcodeToString(int code);

struct Instruction {
    opcode type = NOP;
    double valueNum = 0;
    std::string valueStr = "";
};

// Types de variable dynamique
enum variableType {
  TYPE_NUMBER,
  TYPE_STRING,
  TYPE_BOOLEAN,
  TYPE_LIST,
  TYPE_NULL,
};