#include<iostream>
#include<string>
#include<regex>
#include<fstream>
#include<map>


using namespace std;


string construct_regex(int start, map<int,string> *rules){
        string reg;
        regex nr("\\d+");
        smatch match_nr;
        string str_nr;
        string insert;
        int inserted_11 = 0;
        reg = (*rules)[start];

        while(regex_search(reg, match_nr,nr)){
            for (string str_nr:match_nr){
                insert = (*rules)[stoi(str_nr)];
                if (11 == stoi(str_nr)) inserted_11++;
            }
            cout << insert << endl;
            if (inserted_11 > 6 && insert == "42 31 |  42  11 31") insert = "42 31"; // impossible to match a palindrome, therefore the nubmer of recursions are specified here.
            reg = match_nr.prefix().str() + '(' + insert + ')' + match_nr.suffix().str();
        }
        
        while(reg.find(' ')<reg.length()){
            reg.erase(reg.find(' '),1);
        }

        cout << reg << endl;
        return reg;
}


int main(){
    map<int,string> rules;
    ifstream input_rules("in19rules.data");
    string line;

    while(getline(input_rules,line)){
        int number = stoi(line.substr(0,line.find(':')));
        rules[number] = line.substr(line.find(':')+2);
    }

    string reg = construct_regex(0,&rules);

    regex valid(reg);
    int fits = 0;
    ifstream input_strings("in19.data");
    while (getline(input_strings,line)){
        if (regex_match(line,valid)){
            cout << line;
            cout << "   - fits" << endl;
            fits++;
        }
    }

    cout << "This number fits >> " << fits << endl;
    return 0;
}