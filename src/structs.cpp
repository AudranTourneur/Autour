#include "structs.hpp"

std::string opcodeToString(int code) {
    switch (code) {
    case LOAD_LITERAL:
        return "LOAD_LITERAL";
    case LOAD_VARIABLE:
        return "LOAD_VARIABLE";
    case ADD:
        return "ADD";
    case SUB:
        return "SUB";
    case MUL:
        return "MUL";
    case DIV:
        return "DIV";
    case MOD:
        return "MOD";
    case STORE:
        return "STORE";
    case PRINT:
        return "PRINT";
    case INPUT:
        return "INPUT";
    case NOP:
        return "NOP";
    case SLEEP:
        return "SLEEP";
    case JUMP:
        return "JUMP";
    case JUMP_IF_FALSE:
        return "JUMP_IF_FALSE";
	case CMP_EQ:
		return "CMP_EQ";
	case CMP_NEQ:
		return "CMP_NEQ";
	case CMP_GT:
		return "CMP_GT";
	case CMP_GTE:
		return "CMP_GTE";
	case CMP_LT:
		return "CMP_LT";
	case CMP_LTE:
		return "CMP_LTE";
    case LOGIC_AND:
        return "LOGIC_AND";
    case LOGIC_OR:
        return "LOGIC_OR";
    case LOGIC_NOT:
        return "LOGIC_NOT";
    case NEG:
        return "NEG";
    case MATH_SQRT:
        return "MATH_SQRT";
    case LOAD_LIST:
        return "LOAD_LIST";
    case LOAD_LIST_ITEM:
        return "LOAD_LIST_ITEM";
    case STORE_LIST:
        return "STORE_LIST";
    case GRAPHICS_INIT:
        return "GRAPHICS_INIT";
    case COLOR_PIXEL:
        return "COLOR_PIXEL";
    case GRAPHICS_UPDATE:
        return "GRAPHICS_UPDATE";
    case CALL:
        return "CALL";
    case RETURN:
        return "RETURN";
    default:
        return "UNKNOWN (" + std::to_string(code) + ")";
    }
}