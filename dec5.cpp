#include<iostream>
#include<fstream>
#include<list>
using namespace std;

int partition(char* seat, int upper, int lower, int nvals){
    int value = upper;
    for (int i=0;i<nvals;i++){
        if (seat[i] == 'F' || seat[i] == 'L'){
            upper = upper - (upper-lower)/2 - 1;
        }else if (seat[i] == 'B' || seat[i] == 'R'){
            lower = lower + (upper-lower)/2 + 1;
        }
    }
    if (seat[nvals]=='F' || seat[nvals] == 'L'){
        return lower;
    }else{
        return upper;
    }
    return 0;
}


int main(){
    char array[10];
    ifstream input;
    list<int> seatids;
    input.open("in05.data");
    int row,col,sid, maxsid=0;
    if (input.is_open()){
        while (input.getline(array,11)){
            row = partition(array, 127, 0, 7);
            col = partition(array+7,7,0,3);
            sid = row*8 + col;
            seatids.push_back(sid);
            if (sid>maxsid) maxsid = sid;
        }
         
    }
    cout << "Maximum seat id : " << maxsid << endl;
    seatids.sort();
    int i = 10;
    for (std::list<int>::iterator it=seatids.begin(); it != seatids.end(); ++it){
        i++;
        if (*it != i){
            cout << "Seat found !! : " << i << endl;
            return 0;
        }
    }
}