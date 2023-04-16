#include "VariableWrapper.hpp"

#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

using namespace std;

/*
  Ce fichier implèmente principalement les surcharges d'opérateurs usuels
  (+, -, *, /, %, >, <, >=, <=, ==, !=, &&, ||, -)
  ainsi que quelques méthodes utilitaires simples
*/

// Additionne deux VariableWrapper, si les deux sont des nombres, on fait une addition
// sinon on concatène les deux
VariableWrapper VariableWrapper::operator+(const VariableWrapper &other) {
  VariableWrapper result;
  if (type == TYPE_NUMBER && other.type == TYPE_NUMBER) {
    result.type = TYPE_NUMBER;
    result.valueNumber = valueNumber + other.valueNumber;
  } else {
    result.type = TYPE_STRING;
    result.valueString = formatWrapper(*this) + formatWrapper(other);
  }
  return result;
}

VariableWrapper VariableWrapper::operator-(const VariableWrapper &other) {
  VariableWrapper result;
  if (type == TYPE_NUMBER && other.type == TYPE_NUMBER) {
    result.type = TYPE_NUMBER;
    result.valueNumber = valueNumber - other.valueNumber;
  } else {
    result.type = TYPE_NULL;
  }
  return result;
}

VariableWrapper VariableWrapper::operator/(const VariableWrapper &other) {
  VariableWrapper result;
  if (type == TYPE_NUMBER && other.type == TYPE_NUMBER) {
    result.type = TYPE_NUMBER;
    result.valueNumber = valueNumber / other.valueNumber;
  } else {
    result.type = TYPE_NULL;
  }
  return result;
}

VariableWrapper VariableWrapper::operator*(const VariableWrapper &other) {
  VariableWrapper result;
  if (type == TYPE_NUMBER && other.type == TYPE_NUMBER) {
    result.type = TYPE_NUMBER;
    result.valueNumber = valueNumber * other.valueNumber;
  } else {
    result.type = TYPE_NULL;
  }
  return result;
}

VariableWrapper VariableWrapper::operator%(const VariableWrapper &other) {
  VariableWrapper result;
  if (type == TYPE_NUMBER && other.type == TYPE_NUMBER) {
    result.type = TYPE_NUMBER;
    result.valueNumber = fmod(valueNumber, other.valueNumber);
  } else {
    result.type = TYPE_NULL;
  }
  return result;
}

istream &operator>>(istream &is, VariableWrapper &var) {
  if (var.type == TYPE_NUMBER) {
    is >> var.valueNumber;
  } else if (var.type == TYPE_STRING) {
    is >> var.valueString;
  }
  return is;
}

string VariableWrapper::formatNumber(double x) {
  if (std::trunc(x) == x) {
    return to_string((int)x);
  } else {
    return to_string(x);
  }
}

string VariableWrapper::formatList(std::vector<VariableWrapper> list) {
  string result = "[";
  for (int i = 0; i < list.size(); i++) {
    result += formatWrapper(list[i]);
    if (i < list.size() - 1) {
      result += ", ";
    }
  }
  result += "]";
  return result;
}

// Affichage console d'une variable quelconque
string VariableWrapper::formatWrapper(const VariableWrapper &var) {
  if (var.type == TYPE_NUMBER) {
    return formatNumber(var.valueNumber);
  } else if (var.type == TYPE_STRING) {
    return var.valueString;
  } else if (var.type == TYPE_LIST) {
    return formatList(*var.valueList);
  }
  return "";
}

// Affichage console
ostream &operator<<(ostream &os, VariableWrapper &var) {
  if (var.type == TYPE_NUMBER) {
    os << VariableWrapper::formatNumber(var.valueNumber);
  } else if (var.type == TYPE_STRING) {
    os << var.valueString;
  } else if (var.type == TYPE_LIST) {
    os << "[";
    for (int i = 0; i < var.valueList->size(); i++) {
      os << var.valueList->operator[](i);
      if (i < var.valueList->size() - 1) {
        os << ", ";
      }
    }
    os << "]";
  }
  return os;
}

bool VariableWrapper::operator==(VariableWrapper &var) {
  if (this->type != var.type)
    return false;
  return this->valueNumber == var.valueNumber &&
         this->valueString == var.valueString;
}

bool VariableWrapper::operator!=(VariableWrapper &var) {
  return !(this->operator==(var));
}

bool VariableWrapper::operator>(VariableWrapper &var) {
  if (this->type != TYPE_NUMBER || var.type != TYPE_NUMBER)
    return false;
  return this->valueNumber > var.valueNumber;
}

bool VariableWrapper::operator>=(VariableWrapper &var) {
  if (this->type != TYPE_NUMBER || var.type != TYPE_NUMBER)
    return false;
  return this->valueNumber >= var.valueNumber;
}

bool VariableWrapper::operator<(VariableWrapper &var) {
  if (this->type != TYPE_NUMBER || var.type != TYPE_NUMBER)
    return false;
  return this->valueNumber < var.valueNumber;
}

bool VariableWrapper::operator<=(VariableWrapper &var) {
  if (this->type != TYPE_NUMBER || var.type != TYPE_NUMBER)
    return false;
  return this->valueNumber <= var.valueNumber;
}

// Opérateur de négation unaire pour les nombres
VariableWrapper VariableWrapper::operator-() {
  VariableWrapper result;
  if (type == TYPE_NUMBER) {
    result.type = TYPE_NUMBER;
    result.valueNumber = -valueNumber;
  } else {
    result.type = TYPE_NULL;
  }
  return result;
}

VariableWrapper::VariableWrapper() { type = TYPE_NULL; }

VariableWrapper::VariableWrapper(double d) {
  type = TYPE_NUMBER;
  valueNumber = d;
}

VariableWrapper::VariableWrapper(string s) {
  type = TYPE_STRING;
  valueString = std::move(s);
}

VariableWrapper::VariableWrapper(bool b) {
  type = TYPE_BOOLEAN;
  valueNumber = !b ? 0 : 1;
}

VariableWrapper::VariableWrapper(const std::vector<VariableWrapper> &v) {
  type = TYPE_LIST;
  valueList = std::make_shared<std::vector<VariableWrapper>>(v);
}

// Constructor de recopie
VariableWrapper::VariableWrapper(const VariableWrapper &other) {
  type = other.type;
  valueNumber = other.valueNumber;
  valueString = other.valueString;
  valueList = other.valueList;
}

bool VariableWrapper::getTruthiness() {
  if (type == TYPE_NULL)
    return false;
  if (type == TYPE_BOOLEAN)
    return valueNumber != 0;
  if (type == TYPE_NUMBER)
    return valueNumber != 0;
  if (type == TYPE_STRING)
    return valueString != "";
  if (type == TYPE_LIST)
    return !valueList->empty();
  return false;
}

VariableWrapper &VariableWrapper::operator[](int index) {
  if (type == TYPE_LIST) {
    return valueList->operator[](index);
  }
  return *this;
}

bool VariableWrapper::operator&&(VariableWrapper &other) {
  return this->getTruthiness() && other.getTruthiness(); 
}

bool VariableWrapper::operator||(VariableWrapper &other) {
  return this->getTruthiness() || other.getTruthiness(); 
}