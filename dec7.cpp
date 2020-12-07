#include<fstream>
#include<iostream>
#include<regex>
#include<set>


using namespace std;

ifstream input;
string rege = R"(\d \w* \w* bag)";
regex e(rege);
int sub_bags = 0;
set<string> ided_bags;

void count_bags(string bag){
    string line;
    int pos_in_file;
    input.seekg(0,input.beg);
    while(getline(input,line)){
        int contains = line.find("contain");
        int looking_for = line.find(bag);
        
        string containing_bags = line.substr(contains);
        smatch matches;

        if (looking_for>contains && looking_for<line.length()){
            regex_search(containing_bags,matches,e);
            for (auto x:matches){
            //std::cout << x << "  is contained in " << line.substr(0,contains-6) << endl;
            ided_bags.insert(line.substr(0,contains-6));
            pos_in_file = input.tellg();
            count_bags(line.substr(0,contains-6));
            input.clear();
            input.seekg(pos_in_file,input.beg);
            } 
            //std::cout << std::endl;

        }
    }
};

int number_of_subbags(string bag){
    string line;
    int pos_in_file;
    int sub_bags_this_bag = 0;
    input.seekg(0,input.beg);
    while(getline(input,line)){
        int contains = line.find("contain");
        int looking_for = line.find(bag);
        
        string containing_bags = line.substr(contains);
        smatch matches;
        
        if (looking_for<contains && looking_for<line.length() && looking_for!=-1){
            while(regex_search(containing_bags,matches,e)){
                if (matches.empty()) return 0;
                for (auto x:matches){
                string this_sub_bag = x.str();
                string color  = this_sub_bag.substr(this_sub_bag.find(" ")+1,this_sub_bag.length()-6);
                int multiplier = stoi(this_sub_bag.substr(0,this_sub_bag.find(" ")));

                pos_in_file = input.tellg();
                sub_bags_this_bag += multiplier + multiplier*number_of_subbags(color);
                input.clear();
                input.seekg(pos_in_file,input.beg);
                }
                cout << endl << endl;
                containing_bags = matches.suffix();
            }

        }
    }
    return sub_bags_this_bag;

};


int main(){
    input.open("in07.data");

    count_bags("shiny gold");
    cout << ided_bags.size() << endl;

    cout << number_of_subbags("shiny gold") << endl;
    cout << sub_bags << endl;    

    return 0;
}