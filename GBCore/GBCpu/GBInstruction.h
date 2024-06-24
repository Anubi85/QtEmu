#pragma once

#define NOP_INSTRUCTION 0x00

class GBInstructionContext;
class IGBBus;
class GBCpu;

typedef bool (GBCpu::*GBInstruction)(GBInstructionContext*, IGBBus*);
