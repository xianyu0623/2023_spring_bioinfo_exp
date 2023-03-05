#include "general_heading.h"
#include "sort.h"
#include "C2B.h"
#include "BWT_easy_vers.h"
void read_fasta(std::ifstream &myfile, std::string &seq);
void printBinary(uint64_t n);
int main() {
    std::vector<uint8_t> sequences;
    //open a file
    std::string file = "../NC_008253.fna";
    std::ifstream myfile;
    myfile.open(file);
    std::string  cur_row;
    uint64_t size = 0;
    std::getline(myfile, cur_row);
    while(std::getline(myfile, cur_row)){
        size += cur_row.size();
    }
    myfile.close();
    myfile.open(file);
    uint64_t num_of_u64 = (size * 2) / 64;
    int* SA = (int*) malloc(sizeof(int) * size + 1);
    for(int i = 0 ; i <= size + 1 ; i ++){
        SA[i] = i;
    }
    uint64_t* sequence = (uint64_t *)malloc(sizeof(uint64_t) * num_of_u64 + 1);
    C2B(sequence, myfile);
    //record the time
    clock_t start, finish;
    double totaltime;
    start = clock();
    my_quicksort(SA, 0, size, sequence);
    uint64_t* BWT = (uint64_t *)malloc(sizeof(uint64_t) * num_of_u64 + 1);
    uint64_t loc = C2B_BWT(sequence, BWT, SA, size);
    std::cout << "loc of dollar: " << loc << std::endl;
    finish = clock();
    totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
    std::cout<<"time: "<<totaltime<<"s"<<std::endl;
    std::cout<<"size: "<<size<<std::endl;
//    //打印前10个SA数组的值
//    for(int i = 0 ; i < 10 ; i ++){
//        std::cout << SA[i] << std::endl;
//    }
//    print_BWT(SA, sequence, 1000);
    return 0;
}
//this function is used to print the binary code, just for debug
void printBinary(uint64_t n) {
    std::bitset<64> bits(n);
    std::cout << bits << std::endl;
}





