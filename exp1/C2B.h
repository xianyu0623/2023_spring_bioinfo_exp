//
// Created by PC on 2023/3/4.
//

#ifndef EXP1_C2B_H
#define EXP1_C2B_H
#include "general_heading.h"
void C2B(uint64_t* addr, std::ifstream &infile);
uint64_t encode(char c);
uint32_t C2B_BWT(uint64_t* seq, uint64_t *BWT, int* SA, int size);
#endif //EXP1_C2B_H
