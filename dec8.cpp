#include<fstream>
#include<iostream>
#include<set>
#include<string>
#include<list>
#include<iterator>
using namespace std;


bool run_program(list<pair<string,int>> program){
    int acc = 0;
    list<pair<string,int>>::iterator head = program.begin();
    
    set<int> executed_lines;
    std::pair<std::set<int>::iterator,bool> ret;
    int line = 0;

    while(head != program.end()){
        ret = executed_lines.insert(line);
        if (!ret.second){
            cout << "repeated line " << line << " accu = " << acc << endl; 
            return false;
        }
        pair<string,int> this_command = *head;
        if (this_command.first=="acc"){
            acc += this_command.second;
            ++head;
            ++line;
        }else if (this_command.first=="jmp"){
            advance(head,this_command.second);
            line += this_command.second;
        }else{
            ++head;
            ++line;
        }
    }
    cout << "Successful termination, accu = " << acc << endl;
    return true;
}


int main(){

    ifstream input;
    input.open("in08.data");
    list<pair<string,int>> program;
    string line;
    

    while(getline(input,line)){
        string instruction;
        int argument;  
        instruction = line.substr(0,3);
        argument = stoi(line.substr(4));
        pair<string,int> command(instruction,argument);
        program.push_back(command);
    }

    for (list<pair<string,int>>::iterator it = program.begin(); it!=program.end(); ++it){
        pair<string,int> elem = *it;
        if ((*it).first=="jmp"){
            (*it).first="nop";
            if (run_program(program)) break;
            (*it).first="jmp";
        }else if ((*it).first=="nop"){
            (*it).first="jmp";
            if (run_program(program)) break;
            (*it).first="nop";
        }
    }


    input.close();
    return 0;
}