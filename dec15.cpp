#include<iostream>
#include<map>
using namespace std;

int main(int argc, char *argv[]){

    int most_recent, next_number;
    bool seen;
    int turn = 0;
    map<int,int> numbers;

    int ntrs = stoi(argv[1]);


    //starting numbers
    int starting_numbers[6] = {2,15,0,9,1,20};
    for (int i = 0; i<=4; i++){
        turn ++;
        most_recent = starting_numbers[i];
        numbers[starting_numbers[i]] = turn;
    }

    most_recent = starting_numbers[5];    

    while(turn<ntrs){
        turn++;

        if (numbers.count(most_recent)>0){
            next_number = turn  - numbers[most_recent];
        }else{
            next_number = 0;
        }
        
        if (turn==ntrs) cout << most_recent << endl;
        numbers[most_recent] = turn;
        most_recent = next_number;
    }

    cout << numbers.size() << endl;

    return 0;
}