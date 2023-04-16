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
  Ce lanage ne possède qu'une seule clsse de variable, qui peut changer dynamiquement.
*/

class VariableWrapper {
public:
  variableType type = TYPE_NULL;
  string valueString = "";
  double valueNumber = 0;
  std::shared_ptr<std::vector<VariableWrapper>> valueList;

  VariableWrapper();
  VariableWrapper(double d);
  VariableWrapper(string s);
  VariableWrapper(bool b);
  VariableWrapper(const std::vector<VariableWrapper> &v);
  VariableWrapper(const VariableWrapper &vw);

  VariableWrapper operator+(const VariableWrapper &other);
  VariableWrapper operator-(const VariableWrapper &other);
  VariableWrapper operator/(const VariableWrapper &other);
  VariableWrapper operator*(const VariableWrapper &other);
  VariableWrapper operator%(const VariableWrapper &other);

  friend istream &operator>>(istream &is, VariableWrapper &other);
  friend ostream &operator<<(ostream &os, VariableWrapper &other);

  bool operator==(VariableWrapper &other);
  bool operator!=(VariableWrapper &other);

  bool operator>(VariableWrapper &other);
  bool operator>=(VariableWrapper &other);

  bool operator<(VariableWrapper &other);
  bool operator<=(VariableWrapper &other);

  bool operator&&(VariableWrapper &other);
  bool operator||(VariableWrapper &other);

  VariableWrapper operator-();

  VariableWrapper &operator[](int index);

  static string formatNumber(double x);
  static string formatList(std::vector<VariableWrapper> list);
  static string formatWrapper(const VariableWrapper &var);

  bool getTruthiness();
};