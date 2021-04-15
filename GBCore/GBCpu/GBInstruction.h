#ifndef GBINSTRUCTION_H
#define GBINSTRUCTION_H

class GBInstructionContext;
class GBBus;
class GBCpu;

typedef bool (GBCpu::*GBInstruction)(GBInstructionContext*, GBBus*);

#endif // GBINSTRUCTION_H
