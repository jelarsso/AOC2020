#include<fstream>
#include<iostream>
#include<string>

using namespace std;

int inline periodic(int index, int n){
    return (index+n)%n;
}

int main(){


    ifstream input;
    string line;
    input.open("in03.data");
    int nlines = 323;
    int width = 31;

    char map[323][31];

    if (input.is_open()){
        int iline = 0;
        while(getline(input, line)){
            for (int j=0;j<width;j++) map[iline][j] = line[j];
            iline++;
        }
    }
    int trees = 0;
    char tree = '#';

    long int prod = 1;
    int down[5] = {1,1,1,1,2};
    int left[5] = {1,3,5,7,1};

    for (int k=0;k<5;k++){
        trees = 0;
        for (int i=0;i<nlines;i++){
                if (i*down[k] > nlines) break;
                if (map[i*down[k]][periodic(left[k]*i,width)]==tree) trees++;
        }
        cout << trees << endl;
        prod*=trees;
    }

    cout << prod << endl;


    return 0;
}