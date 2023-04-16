#include "ProgramState.hpp"

#include <array>
#include <map>
#include <stack>
#include <string>
#include <vector>

using namespace std;

void ProgramState::addInstruction(opcode type, double numValue,
                      const string& stringValue) {
    auto *instruction = new Instruction();
    instruction->type = type;
    instruction->valueNum = numValue;
    instruction->valueStr = stringValue;

    allInstructions.push_back(instruction);
    ic++;
  }

int ProgramState::getUniqueInternalId() {
  static int id = 0;
  return id++;
}