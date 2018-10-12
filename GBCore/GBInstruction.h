#ifndef GBINSTRUCTION_H
#define GBINSTRUCTION_H

class GBInstructionContext;
class GBBus;
class IGBCpuStateContext;

typedef bool (IGBCpuStateContext::*GBInstruction)(GBInstructionContext*, GBBus*);

#endif // GBINSTRUCTION_H
