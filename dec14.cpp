#include<fstream>
#include<iostream>
#include<cmath>
#include<string>
#include<list>

using namespace std;


void write_binary(bool *array, int number, int size_array){
    if (pow(2,size_array)<number) throw("Exception!");

    for (int i = 0; i<size_array; i++){
        bool digit = number%2;
        number /= 2;
        if (digit > 1) cout << digit << endl;
        array[i] = digit;
    }
}

void apply_mask(string mask, bool *array, int line_size){
    for (int i = 0; i<line_size; i++){
        if (mask[line_size - i-1] == '0') array[i] = 0;
        else if (mask[line_size - i-1] == '1') array[i] = 1;
    }
}



int part1(){

    int line_size = 36;
    bool *memory;
    list<pair<int,bool*>> memories;

    ifstream input;
    input.open("in14.data");
    string line,mask;
    int memaddr,memwrite;

    while(getline(input,line)){

        
        if (line.find("mask")<line.size()){
            mask = line.substr(7);
        }

        if (line.find("mem")<line.size()){
            memaddr = stoi(line.substr(4,line.length()-line.find("]")));
            memwrite = stoi(line.substr(line.find("=")+1));
            bool flag = true;
            memory = new bool[line_size];
            for (int i=0;i<line_size;i++) memory[i] = 0;

            
            for (list<pair<int,bool*>>::iterator it=memories.begin(); it!=memories.end(); ++it){
                if (it->first == memaddr){
                    delete[] it->second;
                    write_binary(memory,memwrite,line_size);
                    apply_mask(mask, memory, line_size);
                    it->second = memory;
                    flag = false;
                    break;
                }
            }
            if (flag){
            write_binary(memory,memwrite,line_size);
            apply_mask(mask, memory, line_size);
            memories.push_back(pair<int,bool*>(memaddr,memory));   
            }
        }

    }

    long int memsum = 0;
    long int mem = 0;
    
    for (list<pair<int,bool*>>::iterator it=memories.begin(); it!=memories.end(); ++it){
        for (int i = 0; i<line_size; i++){
            if (it->second[i]) mem += pow(2,i);
        }
        if (it->first == 32355) cout << mem << endl;
        memsum += mem;
        mem = 0;
    }

    cout << memsum << endl;

    return 0;
}



list<pair<long int,long int>> memories;
void apply_mask_memory(bool *memaddr, int value, string mask, int line_size){
    for (int i=0;i<line_size;i++){
        if (mask[line_size - i - 1] == 'X'){
            mask[line_size - i - 1] = '0';
            bool orig_val = memaddr[i];
            
            memaddr[i] = 0;
            apply_mask_memory(memaddr,value,mask,line_size);
            memaddr[i] = 1;
            apply_mask_memory(memaddr,value,mask,line_size);

            memaddr[i] = orig_val;
        }
    }
    if (mask.find('X')<mask.length()) return;
 
    long int intaddr = 0;
    for (int i = 0; i<line_size; i++){
        if (memaddr[i] || (mask[line_size-1-i]=='1')) intaddr += pow(2,i);
    }
    bool flag = true;
    for (list<pair<long int,long int>>::iterator it = memories.begin(); it!=memories.end(); ++it){
        if (it->first == intaddr){
            it->second = value;
            flag = false;
            break;
        } 
    }
    if (flag) memories.push_back(pair<long int, long int>(intaddr,value));
}

int part2(){

    int line_size = 36;
    bool *memory;

    ifstream input;
    input.open("in14.data");
    string line,mask;
    int memaddr,memwrite;

    while(getline(input,line)){

        
        if (line.find("mask")<line.size()){
            mask = line.substr(7);
        }

        if (line.find("mem")<line.size()){
            memaddr = stoi(line.substr(4,line.length()-line.find("]")));
            memwrite = stoi(line.substr(line.find("=")+1));
            memory = new bool[line_size];
            for (int i=0;i<line_size;i++) memory[i] = 0;

            write_binary(&memory[0], memaddr, line_size);
            apply_mask_memory(&memory[0],memwrite,mask,line_size);
        }
    }

    unsigned long int memsum = 0;
    
    for (list<pair<long int,long int>>::iterator it=memories.begin(); it!=memories.end(); ++it){
        cout << it->first << " " << it-> second << endl;
        memsum+=it->second;
    }

    cout << memsum << endl;


    return 0;
}


int main(){
    part1();
    part2();
}