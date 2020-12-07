#include<fstream>
#include<iostream>


using namespace std;



int main(){

    ifstream input;

    input.open("in01.data");

    int nlines = 200;
    int numbers[nlines];

    for (int i = 0; i<nlines; i++){
        input >> numbers[i];
    }

    for (int i = 0; i<nlines; i++){
        for (int j = 0; j<i; j++){
            if (j==i) continue;
            for (int k = 0; k<j; k++){
                if (numbers[i] + numbers[j] + numbers[k] == 2020) cout << numbers[i]*numbers[j]*numbers[k] << endl;
            }
        }
    }


    input.close();

    return 0;
}