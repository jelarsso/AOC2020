#include<iostream>
#include<fstream>
#include<list>



using namespace std;

int main(){
    ifstream input;
    input.open("in09.data");
    string line;
    
    list<long int> last_numbers;
    list<long int> all_numbers;
    long int wrong_number;
    int preamble = 25;
    int counter = 0;
    
    while(getline(input,line)){
        long int this_number;
        this_number = stol(line);
        all_numbers.push_back(this_number);
        if (counter<preamble){
        last_numbers.push_back(this_number); 
        counter++; 
        continue;
        }
        bool valid = false;
        for (list<long int>::iterator it1=last_numbers.begin();it1!=last_numbers.end();++it1){
            for (list<long int>::iterator it2=last_numbers.begin();it2!=last_numbers.end();++it2){
                if (*it2 + *it1 == this_number) valid = true;
            }
        }
        if (valid == false){
            cout << "Wrong number found " << this_number << endl;
            wrong_number = this_number;
            break;
        }
        last_numbers.push_back(this_number);
        last_numbers.pop_front();
    }

    long int running_sum = 0;
    list<long int> terms;

    for (list<long int>::iterator it1=all_numbers.begin();it1!=all_numbers.end();++it1){
        if (running_sum < wrong_number){
            running_sum += *it1;
            terms.push_back(*it1);
        }
        while (running_sum > wrong_number){
            running_sum -= terms.front();
            terms.pop_front();
        }
        if (running_sum == wrong_number){
            cout << "FOUND!! " << endl;
            terms.sort();
            cout << terms.front() + terms.back() << endl;
        }
    }

    input.close();
    return 0;
}