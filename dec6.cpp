#include<fstream>
#include<iostream>
#include<string>

using namespace std;

int unique_answers_in_group(string group){
    cout << group << endl;

    for(int li = 0; li<group.length(); li++){
        for (int li2 = li+1; li2<group.length(); li2++){
            if (group[li2]==group[li]){
                group.erase(li2,1);
                li2--;
                }   
        }
    }
    cout << group << endl;
    return group.length();
}

int everyone_answered(string group, int persons_in_group){
    int everyone_answered_yes = 0;
    int q_counter = 0;
    for (int li = 0; li<group.length(); li++){
        for (int li2 = li+1; li2<group.length(); li2++){
            if (group[li2]==group[li]){
                group.erase(li2,1);
                li2--;
                q_counter++;
            }
        }
        if (q_counter+1 == persons_in_group) everyone_answered_yes++; q_counter=0;
    }
    cout << group << endl;
    return everyone_answered_yes;
}

int main(){
    ifstream input;
    input.open("in06.data");
    
    string this_line,group;
    
    int yes_answers = 0;
    int persons_in_group = 0;
    int questions_in_group = 0;
    int everyone_answered_yes = 0;


    if (input.is_open()){
        while(getline(input,this_line)){
            if (this_line.length()>0){
                group += this_line;
                persons_in_group++;
            }else{
                //questions_in_group = unique_answers_in_group(group);
                cout << group << endl;
                everyone_answered_yes = everyone_answered(group,persons_in_group);
                yes_answers += everyone_answered_yes;
                cout << "Qs: " << everyone_answered_yes << " Ppl: " << persons_in_group << endl << endl;
                persons_in_group = 0;
                everyone_answered_yes = 0;
                group.clear();
            }
        }
    }

    cout << yes_answers << endl;


    return 0;
}