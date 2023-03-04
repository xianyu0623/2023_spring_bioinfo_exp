//
// Created by PC on 2023/3/4.
//

#include "general_heading.h"
//convert the char into the 00,01,10,11
uint64_t encode(char c) {
    switch (c) {
        case ('A') :
            return 0;//00
        case ('C') :
            return 1;//01
        case ('G') :
            return 2;//10
        case ('T') :
            return 3;//11
        default:
            return -1;
    }
}
//this function is used to convert the char into the binary code
void C2B(uint64_t* addr, std::ifstream &infile){
    if(!infile.is_open()){
        std::cout << "ERROR: No such file or directory." <<std::endl;
        return;
    }
    short bits = 0;
    uint64_t cur = 0;
    long i = -1;
    std::string cur_row;
    std::getline(infile, cur_row);
    while(std::getline(infile, cur_row)){
        for(char c : cur_row){
            uint64_t cur_char = encode(c);
            if(cur_char == -1){
                std::cout << "ERROR: A character is not one of \'ACGT\' " <<std::endl;
                return;
            }

            if(bits == 0){
                if (i == -1){
                    i++;
                }else{
                    addr[i++] = cur;
                }
                cur = cur_char;
                bits = 62;
            }else{
                cur = (cur << 2) | cur_char;
                bits -= 2;
            }
        }
    }
    if(bits){
        cur = cur << bits;
        addr[i] = cur;
    }
}
