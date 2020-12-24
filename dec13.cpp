#include<iostream>
#include<cmath>


using namespace std;


int main(){
    //part 1
    /*int earliest = 1000655;
    int short_buses[9] = {17,37,571,13,23,29,401,41,19};
    while(true){
        for (int i = 0; i<9; i++){
            if (earliest%short_buses[i]==0) {cout << short_buses[i]*(earliest-1000655)<< endl; return 0;}
        }
        earliest++;
    }*/

    //part 2
    int numbers = 68;
    int buses[numbers] = {17,0,0,0,0,0,0,0,0,0,0,37,0,0,0,0,0,571,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,13,0,0,0,0,23,0,0,0,0,0,29,0,401,0,0,0,0,0,0,0,0,0,41,0,0,0,0,0,0,0,0,19};

    //int numbers = 4;
    //int buses[numbers] = {1789,37,47,1889};
    
    
    bool buses_jumper[numbers];

    for (int n = 0; n<numbers; n++) buses_jumper[n] = true;
        
    int jumper = buses[0];
    unsigned long long int time = jumper;
    bool flag = true;

    while (flag){

        for (int n = 0; n<numbers; n++){
            if (buses[n]==0) continue;

            if (time%buses[n]==buses[n]-n && buses_jumper[n]) {
                jumper*=buses[n];
                buses_jumper[n] = false;
            }
        }
        time += jumper;
        for (int n=0;n<numbers;n++){
            flag = true;
            if (buses[n]==0) continue;
            if ((time+n)%buses[n]!=0) break;
            flag = false;
        }
    cout << time << endl;
    }
    
    

    return 0;
}