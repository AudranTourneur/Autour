#pragma once

#include <string>

// Définition des types d'opcode
enum opcode {
    NOP,
    LOAD_LITERAL,
    LOAD_VARIABLE,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    STORE,
    PRINT,
    INPUT,
    CALL,
    RETURN,
    HALT,
    SLEEP,
    JUMP,
    JUMP_IF_FALSE,
	CMP_EQ,
	CMP_GT,
	CMP_GTE,
	CMP_LT,
	CMP_LTE,
	CMP_NEQ,
    LOGIC_AND,
    LOGIC_OR,
    LOGIC_NOT,
    NEG,
    MATH_SQRT,
    LOAD_LIST,
    LOAD_LIST_ITEM,
    STORE_LIST,
    GRAPHICS_INIT,
    COLOR_PIXEL,
    GRAPHICS_UPDATE,
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