//
// Created by PC on 2023/3/4.
#include "general_heading.h"

char extract_char(uint64_t* addr, int idx){
    int i = idx / 32;
    int j = idx % 32;
    uint64_t code = addr[i];
    code = (code << j * 2) >> 62;//get the bits we want: shift left j*2 bits, then shift right 62 bits
    switch (code) {
        case(0) : return 'A';
        case(1) : return 'C';
        case(2) : return 'G';
        case(3) : return 'T';
        default: return 'N';
    }
}

uint64_t extract_val(uint64_t* addr, int idx){
    int i = idx >> 5 ;
    int j = idx % 32;
    if(j == 0) return addr[i];
    uint64_t code1 = addr[i];
    code1 = (code1 << j * 2);
    uint64_t code2 = addr[i + 1];
    code2 = code2 >> (64 - j * 2);
    uint64_t res = code1 | code2;
    return res;

}

int compare(uint64_t* addr, int i, int j){
    uint64_t val1, val2;
    val1 = extract_val(addr, i);
    val2 = extract_val(addr, j);
    if(val1 == val2) return (compare(addr, i + 1, j + 1));
    else return extract_val(addr, i) < extract_val(addr, j);
}


void my_quicksort(int SA[], int left, int right, uint64_t* addr) {
    if (left < right) {
        int pivot = SA[right];
        int i = left - 1;
        for (int j = left; j <= right - 1; j++) {
            if (compare(addr,SA[j], pivot)) {
                i++;
                std::swap(SA[i], SA[j]);
            }
        }
        std::swap(SA[i + 1], SA[right]);
        int partition = i + 1;
        my_quicksort(SA, left, partition - 1, addr);
        my_quicksort(SA, partition + 1, right, addr);
    }
}