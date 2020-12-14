#include<fstream>
#include<iostream>
#include<list>
#include<string>


using namespace std;

long int valid_arrangement = 0;
list<int> adapters;

void follow_arrangements(list<int>::iterator this_adapter){
    int this_adapter_value = *this_adapter;
    list<int>::iterator next_adapter = this_adapter;
    int next_adapter_value;
    for (int i=1; i<=3; i++){
        advance(next_adapter,1);
        next_adapter_value = *next_adapter;
        if (next_adapter_value-this_adapter_value<=3){
            if (next_adapter == --adapters.end()){
                valid_arrangement++;
                return;
            }
            follow_arrangements(next_adapter);
        }else{
            return;
        }
    }
};


list<pair<int,long int>> seen_adapters;
long int forward_count(list<int>::iterator this_adapter){

    int this_adapter_value = *this_adapter;
    list<int>::iterator next_adapter = this_adapter;
    int next_adapter_value;
    long int counts = 0;

    for (int i=1; i<=3; i++){
        advance(next_adapter,1);
        next_adapter_value = *next_adapter;
        if (next_adapter_value-this_adapter_value<=3){
            if (next_adapter == --adapters.end()){
                counts++;
                break;
            }else{
                bool seen = 0;
                for (list<pair<int,long int>>::iterator it = seen_adapters.begin();it!=seen_adapters.end();++it){
                    if (it->first == *next_adapter){
                        counts+=it->second;
                        seen = 1;
                        break;
                    }
                }
                if (!seen){
                    seen_adapters.push_back(pair<int,long int>(next_adapter_value,forward_count(next_adapter)));
                    counts += seen_adapters.back().second;
                }
            }
        }
    }
    return counts;
}


int main(){
    ifstream input;
    input.open("in10.data");
    string line;
    int adapter;
    while(getline(input,line)){
        adapter = stoi(line);
        adapters.push_back(adapter);
    }

    /*
    int ones = 0;
    int threes = 1;
    int last_adapter = 0;
    for (list<int>::iterator it = adapters.begin(); it!=adapters.end(); ++it){
        cout << *it - last_adapter << "  " << *it << endl;
        if (*it - last_adapter == 1) ones++;
        if (*it - last_adapter == 3) threes++;
        last_adapter = *it;
        
    }
    cout << ones << " " << threes << endl;
    cout << ones*threes << endl;*/
    adapters.sort();
    adapters.push_front(0);

    cout <<  forward_count(adapters.begin()) << endl;


    return 0;
}