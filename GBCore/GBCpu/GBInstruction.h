#pragma once

#define NOP_INSTRUCTION 0x00

class GBInstructionContext;
class GBBus;
class GBCpu;

typedef bool (GBCpu::*GBInstruction)(GBInstructionContext*, GBBus*);
