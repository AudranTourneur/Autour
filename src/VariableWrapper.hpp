#include "structs.hpp"

#include <cmath>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <memory>

using namespace std;

/*
  Représente une variable, qui peut être de type nombre, chaîne de caractères,
  liste ou booléen.
  Ce langage ne possède qu'une seule clsse de variable, qui peut changer dynamiquement.
*/

class VariableWrapper {
public:
  variableType type = TYPE_NULL; // Le type de la variable
  string valueString = ""; // La valeur de la variable, si elle est de type chaîne de caractères
  double valueNumber = 0; // La valeur de la variable, si elle est de type nombre ou bien booléen (0 ou 1 dans ce cas)
  std::shared_ptr<std::vector<VariableWrapper>> valueList; // La valeur de la variable, si elle est de type liste

  // Constructeurs
  VariableWrapper();
  VariableWrapper(double d);
  VariableWrapper(string s);
  VariableWrapper(bool b);
  VariableWrapper(const std::vector<VariableWrapper> &v);
  VariableWrapper(const VariableWrapper &vw);

  // Opérateurs mathématiques usuels, le + est surchargé pour faire des concaténations en plus
  VariableWrapper operator+(const VariableWrapper &other);
  VariableWrapper operator-(const VariableWrapper &other);
  VariableWrapper operator/(const VariableWrapper &other);
  VariableWrapper operator*(const VariableWrapper &other);
  VariableWrapper operator%(const VariableWrapper &other);

  // Gestion de la console
  friend istream &operator>>(istream &is, VariableWrapper &other);
  friend ostream &operator<<(ostream &os, VariableWrapper &other);

  // Opérateurs de comparaison
  bool operator==(VariableWrapper &other);
  bool operator!=(VariableWrapper &other);

  bool operator>(VariableWrapper &other);
  bool operator>=(VariableWrapper &other);

  bool operator<(VariableWrapper &other);
  bool operator<=(VariableWrapper &other);

  // Opérateurs booléens
  bool operator&&(VariableWrapper &other);
  bool operator||(VariableWrapper &other);

  // Opérateur de négation unaire pour les nombres
  VariableWrapper operator-();

  // Opérateur d'accès à un élément d'une liste
  VariableWrapper &operator[](int index);

  // Fonctions utilitaires de formatage
  static string formatNumber(double x);
  static string formatList(std::vector<VariableWrapper> list);
  static string formatWrapper(const VariableWrapper &var);

  // Renvoie la valeur booléenne de la variable ("truthy" ou "falsy")
  bool getTruthiness();
};