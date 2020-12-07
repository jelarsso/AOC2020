#include<fstream>
#include<iostream>
#include<string>


using namespace std;


int main(){
    ifstream input;

    string line;
    input.open("in02.data");
    int valid_pw = 0;
    int low_occ, high_occ, actual_occ;
    char character;


    if (input.is_open()){
        while(getline(input,line)){
            actual_occ = 0;
            int digits = line.find("-");
            low_occ = stoi(line.substr(0,digits));

            int digits_end = line.find(" ");
            high_occ = stoi(line.substr(digits+1,digits_end));
            
            character = line[digits_end+1];

            char char1,char2;

            char1 = line[digits_end+3+low_occ];
            char2 = line[digits_end+3+high_occ];

            if (char1==character ^ char2==character) valid_pw++;
            /*
            for (int i=digits_end+4; i<line.length(); i++){
                if (line[i]==character) actual_occ++;
            } 
            cout << actual_occ << "\n";
            if (actual_occ<=high_occ && actual_occ>=low_occ) valid_pw++;
            */
            
        }
    }
    input.close();

    cout << valid_pw << endl;


    return 0;
}
