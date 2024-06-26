#include "GBCpu.h"

GBInstruction GBCpu::s_InstructionTable[INSTRUCTIONS_NUM] =
{
    //Regular instruction set
    &GBCpu::NOP,        //0x00
	&GBCpu::LD_rr_nn,   //0x01
	&GBCpu::LD_addr_A,  //0x02
	&GBCpu::INC_rr,     //0x03
	&GBCpu::INC_r,      //0x04
	&GBCpu::DEC_r,      //0x05
	&GBCpu::LD_r_n,     //0x06
	nullptr,            //0x07
	nullptr,            //0x08
	nullptr,            //0x09
	&GBCpu::LD_A_addr,  //0x0A
	&GBCpu::DEC_rr,     //0x0B
	&GBCpu::INC_r,      //0x0C
	&GBCpu::DEC_r,      //0x0D
	&GBCpu::LD_r_n,     //0x0E
	nullptr,            //0x0F
	nullptr,            //0x10
	&GBCpu::LD_rr_nn,   //0x11
	&GBCpu::LD_addr_A,  //0x12
	&GBCpu::INC_rr,     //0x13
	&GBCpu::INC_r,      //0x14
	&GBCpu::DEC_r,      //0x15
	&GBCpu::LD_r_n,     //0x16
	&GBCpu::RLA,        //0x17
	&GBCpu::JR,         //0x18
	nullptr,            //0x19
	&GBCpu::LD_A_addr,  //0x1A
	&GBCpu::DEC_rr,     //0x1B
	&GBCpu::INC_r,      //0x1C
	&GBCpu::DEC_r,      //0x1D
	&GBCpu::LD_r_n,     //0x1E
	nullptr,            //0x1F
	&GBCpu::JR,         //0x20
	&GBCpu::LD_rr_nn,   //0x21
	&GBCpu::LDI,        //0x22
	&GBCpu::INC_rr,     //0x23
	&GBCpu::INC_r,      //0x24
	&GBCpu::DEC_r,      //0x25
	&GBCpu::LD_r_n,     //0x26
	nullptr,            //0x27
	&GBCpu::JR,         //0x28
	nullptr,            //0x29
	&GBCpu::LDI,        //0x2A
	&GBCpu::DEC_rr,     //0x2B
	&GBCpu::INC_r,      //0x2C
	&GBCpu::DEC_r,      //0x2D
	&GBCpu::LD_r_n,     //0x2E
	nullptr,            //0x2F
	&GBCpu::JR,         //0x30
	&GBCpu::LD_rr_nn,   //0x31
	&GBCpu::LDD,        //0x32
	&GBCpu::INC_rr,     //0x33
	&GBCpu::INC_r,      //0x34
	&GBCpu::DEC_r,      //0x35
	&GBCpu::LD_r_n,     //0x36
	nullptr,            //0x37
	&GBCpu::JR,         //0x38
	nullptr,            //0x39
	&GBCpu::LDD,        //0x3A
	&GBCpu::DEC_rr,     //0x3B
	&GBCpu::INC_r,      //0x3C
	&GBCpu::DEC_r,      //0x3D
	&GBCpu::LD_r_n,     //0x3E
	nullptr,            //0x3F
	&GBCpu::LD_r1_r2,   //0x40
	&GBCpu::LD_r1_r2,   //0x41
	&GBCpu::LD_r1_r2,   //0x42
	&GBCpu::LD_r1_r2,   //0x43
	&GBCpu::LD_r1_r2,   //0x44
	&GBCpu::LD_r1_r2,   //0x45
	&GBCpu::LD_r1_r2,   //0x46
	&GBCpu::LD_r1_r2,   //0x47
	&GBCpu::LD_r1_r2,   //0x48
	&GBCpu::LD_r1_r2,   //0x49
	&GBCpu::LD_r1_r2,   //0x4A
	&GBCpu::LD_r1_r2,   //0x4B
	&GBCpu::LD_r1_r2,   //0x4C
	&GBCpu::LD_r1_r2,   //0x4D
	&GBCpu::LD_r1_r2,   //0x4E
	&GBCpu::LD_r1_r2,   //0x4F
	&GBCpu::LD_r1_r2,   //0x50
	&GBCpu::LD_r1_r2,   //0x51
	&GBCpu::LD_r1_r2,   //0x52
	&GBCpu::LD_r1_r2,   //0x53
	&GBCpu::LD_r1_r2,   //0x54
	&GBCpu::LD_r1_r2,   //0x55
	&GBCpu::LD_r1_r2,   //0x56
	&GBCpu::LD_r1_r2,   //0x57
	&GBCpu::LD_r1_r2,   //0x58
	&GBCpu::LD_r1_r2,   //0x59
	&GBCpu::LD_r1_r2,   //0x5A
	&GBCpu::LD_r1_r2,   //0x5B
	&GBCpu::LD_r1_r2,   //0x5C
	&GBCpu::LD_r1_r2,   //0x5D
	&GBCpu::LD_r1_r2,   //0x5E
	&GBCpu::LD_r1_r2,   //0x5F
	&GBCpu::LD_r1_r2,   //0x60
	&GBCpu::LD_r1_r2,   //0x61
	&GBCpu::LD_r1_r2,   //0x62
	&GBCpu::LD_r1_r2,   //0x63
	&GBCpu::LD_r1_r2,   //0x64
	&GBCpu::LD_r1_r2,   //0x65
	&GBCpu::LD_r1_r2,   //0x66
	&GBCpu::LD_r1_r2,   //0x67
	&GBCpu::LD_r1_r2,   //0x68
	&GBCpu::LD_r1_r2,   //0x69
	&GBCpu::LD_r1_r2,   //0x6A
	&GBCpu::LD_r1_r2,   //0x6B
	&GBCpu::LD_r1_r2,   //0x6C
	&GBCpu::LD_r1_r2,   //0x6D
	&GBCpu::LD_r1_r2,   //0x6E
	&GBCpu::LD_r1_r2,   //0x6F
	&GBCpu::LD_r1_r2,   //0x70
	&GBCpu::LD_r1_r2,   //0x71
	&GBCpu::LD_r1_r2,   //0x72
	&GBCpu::LD_r1_r2,   //0x73
	&GBCpu::LD_r1_r2,   //0x74
	&GBCpu::LD_r1_r2,   //0x75
	nullptr,            //0x76
	&GBCpu::LD_r1_r2,   //0x77
	&GBCpu::LD_r1_r2,   //0x78
	&GBCpu::LD_r1_r2,   //0x79
	&GBCpu::LD_r1_r2,   //0x7A
	&GBCpu::LD_r1_r2,   //0x7B
	&GBCpu::LD_r1_r2,   //0x7C
	&GBCpu::LD_r1_r2,   //0x7D
	&GBCpu::LD_r1_r2,   //0x7E
	&GBCpu::LD_r1_r2,   //0x7F
	&GBCpu::ADD,        //0x80
	&GBCpu::ADD,        //0x81
	&GBCpu::ADD,        //0x82
	&GBCpu::ADD,        //0x83
	&GBCpu::ADD,        //0x84
	&GBCpu::ADD,        //0x85
	&GBCpu::ADD,        //0x86
	&GBCpu::ADD,        //0x87
	nullptr,            //0x88
	nullptr,            //0x89
	nullptr,            //0x8A
	nullptr,            //0x8B
	nullptr,            //0x8C
	nullptr,            //0x8D
	nullptr,            //0x8E
	nullptr,            //0x8F
	&GBCpu::SUB,        //0x90
	&GBCpu::SUB,        //0x91
	&GBCpu::SUB,        //0x92
	&GBCpu::SUB,        //0x93
	&GBCpu::SUB,        //0x94
	&GBCpu::SUB,        //0x95
	&GBCpu::SUB,        //0x96
	&GBCpu::SUB,        //0x97
	nullptr,            //0x98
	nullptr,            //0x99
	nullptr,            //0x9A
	nullptr,            //0x9B
	nullptr,            //0x9C
	nullptr,            //0x9D
	nullptr,            //0x9E
	nullptr,            //0x9F
	nullptr,            //0xA0
	nullptr,            //0xA1
	nullptr,            //0xA2
	nullptr,            //0xA3
	nullptr,            //0xA4
	nullptr,            //0xA5
	nullptr,            //0xA6
	nullptr,            //0xA7
	&GBCpu::XOR,        //0xA8
	&GBCpu::XOR,        //0xA9
	&GBCpu::XOR,        //0xAA
	&GBCpu::XOR,        //0xAB
	&GBCpu::XOR,        //0xAC
	&GBCpu::XOR,        //0xAD
	&GBCpu::XOR,        //0xAE
	&GBCpu::XOR,        //0xAF
	&GBCpu::OR,         //0xB0
	&GBCpu::OR,         //0xB1
	&GBCpu::OR,         //0xB2
	&GBCpu::OR,         //0xB3
	&GBCpu::OR,         //0xB4
	&GBCpu::OR,         //0xB5
	&GBCpu::OR,         //0xB6
	&GBCpu::OR,         //0xB7
	&GBCpu::CP,         //0xB8
	&GBCpu::CP,         //0xB9
	&GBCpu::CP,         //0xBA
	&GBCpu::CP,         //0xBB
	&GBCpu::CP,         //0xBC
	&GBCpu::CP,         //0xBD
	&GBCpu::CP,         //0xBE
	&GBCpu::CP,         //0xBF
	&GBCpu::RET,        //0xC0
	&GBCpu::POP,        //0xC1
    &GBCpu::JP,         //0xC2
    &GBCpu::JP,         //0xC3
	&GBCpu::CALL,       //0xC4
	&GBCpu::PUSH,       //0xC5
	&GBCpu::ADD,        //0xC6
	nullptr,            //0xC7
	&GBCpu::RET,        //0xC8
	&GBCpu::RET,        //0xC9
    &GBCpu::JP,         //0xCA
	nullptr,            //0xCB
	&GBCpu::CALL,       //0xCC
	&GBCpu::CALL,       //0xCD
	nullptr,            //0xCE
	nullptr,            //0xCF
	&GBCpu::RET,        //0xD0
	&GBCpu::POP,        //0xD1
    &GBCpu::JP,         //0xD2
	nullptr,            //0xD3
	&GBCpu::CALL,       //0xD4
	&GBCpu::PUSH,       //0xD5
	&GBCpu::SUB,        //0xD6
	nullptr,            //0xD7
	&GBCpu::RET,        //0xD8
	nullptr,            //0xD9
    &GBCpu::JP,         //0xDA
	nullptr,            //0xDB
	&GBCpu::CALL,       //0xDC
	nullptr,            //0xDD
	nullptr,            //0xDE
	nullptr,            //0xDF
	&GBCpu::LD_off_A,   //0xE0
	&GBCpu::POP,        //0xE1
	&GBCpu::LD_off_A,   //0xE2
	nullptr,            //0xE3
	nullptr,            //0xE4
	&GBCpu::PUSH,       //0xE5
	nullptr,            //0xE6
	nullptr,            //0xE7
	nullptr,            //0xE8
	nullptr,            //0xE9
	&GBCpu::LD_addr_A,  //0xEA
	nullptr,            //0xEB
	nullptr,            //0xEC
	nullptr,            //0xED
	&GBCpu::XOR,        //0xEE
	nullptr,            //0xEF
	&GBCpu::LD_A_off,   //0xF0
	&GBCpu::POP,        //0xF1
	&GBCpu::LD_A_off,   //0xF2
	&GBCpu::EDI,        //0xF3
	nullptr,            //0xF4
	&GBCpu::PUSH,       //0xF5
	&GBCpu::OR,         //0xF6
	nullptr,            //0xF7
	nullptr,            //0xF8
	nullptr,            //0xF9
	&GBCpu::LD_A_addr,  //0xFA
	&GBCpu::EDI,        //0xFB
	nullptr,            //0xFC
	nullptr,            //0xFD
	&GBCpu::CP,         //0xFE
	nullptr,            //0xFF
};

GBInstruction GBCpu::s_CBInstructionTable[INSTRUCTIONS_NUM] =
{
    //Regular instruction set
	nullptr,            //0x00
	nullptr,            //0x01
	nullptr,            //0x02
	nullptr,            //0x03
	nullptr,            //0x04
	nullptr,            //0x05
	nullptr,            //0x06
	nullptr,            //0x07
	nullptr,            //0x08
	nullptr,            //0x09
	nullptr,            //0x0A
	nullptr,            //0x0B
	nullptr,            //0x0C
	nullptr,            //0x0D
	nullptr,            //0x0E
	nullptr,            //0x0F
	&GBCpu::RL,         //0x10
	&GBCpu::RL,         //0x11
	&GBCpu::RL,         //0x12
	&GBCpu::RL,         //0x13
	&GBCpu::RL,         //0x14
	&GBCpu::RL,         //0x15
	&GBCpu::RL,         //0x16
	&GBCpu::RL,         //0x17
	nullptr,            //0x18
	nullptr,            //0x19
	nullptr,            //0x1A
	nullptr,            //0x1B
	nullptr,            //0x1C
	nullptr,            //0x1D
	nullptr,            //0x1E
	nullptr,            //0x1F
	nullptr,            //0x20
	nullptr,            //0x21
	nullptr,            //0x22
	nullptr,            //0x23
	nullptr,            //0x24
	nullptr,            //0x25
	nullptr,            //0x26
	nullptr,            //0x27
	nullptr,            //0x28
	nullptr,            //0x29
	nullptr,            //0x2A
	nullptr,            //0x2B
	nullptr,            //0x2C
	nullptr,            //0x2D
	nullptr,            //0x2E
	nullptr,            //0x2F
	nullptr,            //0x30
	nullptr,            //0x31
	nullptr,            //0x32
	nullptr,            //0x33
	nullptr,            //0x34
	nullptr,            //0x35
	nullptr,            //0x36
	nullptr,            //0x37
	nullptr,            //0x38
	nullptr,            //0x39
	nullptr,            //0x3A
	nullptr,            //0x3B
	nullptr,            //0x3C
	nullptr,            //0x3D
	nullptr,            //0x3E
	nullptr,            //0x3F
	&GBCpu::BIT,        //0x40
	&GBCpu::BIT,        //0x41
	&GBCpu::BIT,        //0x42
	&GBCpu::BIT,        //0x43
	&GBCpu::BIT,        //0x44
	&GBCpu::BIT,        //0x45
	&GBCpu::BIT,        //0x46
	&GBCpu::BIT,        //0x47
	&GBCpu::BIT,        //0x48
	&GBCpu::BIT,        //0x49
	&GBCpu::BIT,        //0x4A
	&GBCpu::BIT,        //0x4B
	&GBCpu::BIT,        //0x4C
	&GBCpu::BIT,        //0x4D
	&GBCpu::BIT,        //0x4E
	&GBCpu::BIT,        //0x4F
	&GBCpu::BIT,        //0x50
	&GBCpu::BIT,        //0x51
	&GBCpu::BIT,        //0x52
	&GBCpu::BIT,        //0x53
	&GBCpu::BIT,        //0x54
	&GBCpu::BIT,        //0x55
	&GBCpu::BIT,        //0x56
	&GBCpu::BIT,        //0x57
	&GBCpu::BIT,        //0x58
	&GBCpu::BIT,        //0x59
	&GBCpu::BIT,        //0x5A
	&GBCpu::BIT,        //0x5B
	&GBCpu::BIT,        //0x5C
	&GBCpu::BIT,        //0x5D
	&GBCpu::BIT,        //0x5E
	&GBCpu::BIT,        //0x5F
	&GBCpu::BIT,        //0x60
	&GBCpu::BIT,        //0x61
	&GBCpu::BIT,        //0x62
	&GBCpu::BIT,        //0x63
	&GBCpu::BIT,        //0x64
	&GBCpu::BIT,        //0x65
	&GBCpu::BIT,        //0x66
	&GBCpu::BIT,        //0x67
	&GBCpu::BIT,        //0x68
	&GBCpu::BIT,        //0x69
	&GBCpu::BIT,        //0x6A
	&GBCpu::BIT,        //0x6B
	&GBCpu::BIT,        //0x6C
	&GBCpu::BIT,        //0x6D
	&GBCpu::BIT,        //0x6E
	&GBCpu::BIT,        //0x6F
	&GBCpu::BIT,        //0x70
	&GBCpu::BIT,        //0x71
	&GBCpu::BIT,        //0x72
	&GBCpu::BIT,        //0x73
	&GBCpu::BIT,        //0x74
	&GBCpu::BIT,        //0x75
	&GBCpu::BIT,        //0x76
	&GBCpu::BIT,        //0x77
	&GBCpu::BIT,        //0x78
	&GBCpu::BIT,        //0x79
	&GBCpu::BIT,        //0x7A
	&GBCpu::BIT,        //0x7B
	&GBCpu::BIT,        //0x7C
	&GBCpu::BIT,        //0x7D
	&GBCpu::BIT,        //0x7E
	&GBCpu::BIT,        //0x7F
	nullptr,            //0x80
	nullptr,            //0x81
	nullptr,            //0x82
	nullptr,            //0x83
	nullptr,            //0x84
	nullptr,            //0x85
	nullptr,            //0x86
	nullptr,            //0x87
	nullptr,            //0x88
	nullptr,            //0x89
	nullptr,            //0x8A
	nullptr,            //0x8B
	nullptr,            //0x8C
	nullptr,            //0x8D
	nullptr,            //0x8E
	nullptr,            //0x8F
	nullptr,            //0x90
	nullptr,            //0x91
	nullptr,            //0x92
	nullptr,            //0x93
	nullptr,            //0x94
	nullptr,            //0x95
	nullptr,            //0x96
	nullptr,            //0x97
	nullptr,            //0x98
	nullptr,            //0x99
	nullptr,            //0x9A
	nullptr,            //0x9B
	nullptr,            //0x9C
	nullptr,            //0x9D
	nullptr,            //0x9E
	nullptr,            //0x9F
	nullptr,            //0xA0
	nullptr,            //0xA1
	nullptr,            //0xA2
	nullptr,            //0xA3
	nullptr,            //0xA4
	nullptr,            //0xA5
	nullptr,            //0xA6
	nullptr,            //0xA7
	nullptr,            //0xA8
	nullptr,            //0xA9
	nullptr,            //0xAA
	nullptr,            //0xAB
	nullptr,            //0xAC
	nullptr,            //0xAD
	nullptr,            //0xAE
	nullptr,            //0xAF
	nullptr,            //0xB0
	nullptr,            //0xB1
	nullptr,            //0xB2
	nullptr,            //0xB3
	nullptr,            //0xB4
	nullptr,            //0xB5
	nullptr,            //0xB6
	nullptr,            //0xB7
	nullptr,            //0xB8
	nullptr,            //0xB9
	nullptr,            //0xBA
	nullptr,            //0xBB
	nullptr,            //0xBC
	nullptr,            //0xBD
	nullptr,            //0xBE
	nullptr,            //0xBF
	nullptr,            //0xC0
	nullptr,            //0xC1
	nullptr,            //0xC2
	nullptr,            //0xC3
	nullptr,            //0xC4
	nullptr,            //0xC5
	nullptr,            //0xC6
	nullptr,            //0xC7
	nullptr,            //0xC8
	nullptr,            //0xC9
	nullptr,            //0xCA
	nullptr,            //0xCB
	nullptr,            //0xCC
	nullptr,            //0xCD
	nullptr,            //0xCE
	nullptr,            //0xCF
	nullptr,            //0xD0
	nullptr,            //0xD1
	nullptr,            //0xD2
	nullptr,            //0xD3
	nullptr,            //0xD4
	nullptr,            //0xD5
	nullptr,            //0xD6
	nullptr,            //0xD7
	nullptr,            //0xD8
	nullptr,            //0xD9
	nullptr,            //0xDA
	nullptr,            //0xDB
	nullptr,            //0xDC
	nullptr,            //0xDD
	nullptr,            //0xDE
	nullptr,            //0xDF
	nullptr,            //0xE0
	nullptr,            //0xE1
	nullptr,            //0xE2
	nullptr,            //0xE3
	nullptr,            //0xE4
	nullptr,            //0xE5
	nullptr,            //0xE6
	nullptr,            //0xE7
	nullptr,            //0xE8
	nullptr,            //0xE9
	nullptr,            //0xEA
	nullptr,            //0xEB
	nullptr,            //0xEC
	nullptr,            //0xED
	nullptr,            //0xEE
	nullptr,            //0xEF
	nullptr,            //0xF0
	nullptr,            //0xF1
	nullptr,            //0xF2
	nullptr,            //0xF3
	nullptr,            //0xF4
	nullptr,            //0xF5
	nullptr,            //0xF6
	nullptr,            //0xF7
	nullptr,            //0xF8
	nullptr,            //0xF9
	nullptr,            //0xFA
	nullptr,            //0xFB
	nullptr,            //0xFC
	nullptr,            //0xFD
	nullptr,            //0xFE
	nullptr,            //0xFF
};
