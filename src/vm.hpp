#pragma once

#include "ProgramState.hpp"
#include "structs.hpp"

opcode executeNextInstruction(ProgramState &ps, bool automaticTermination = true);