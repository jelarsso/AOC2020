#include<fstream>
#include<iostream>
#include<cmath>


using namespace std;


const double pi =  3.14159265358979323846 ;


int main(){
    ifstream input;
    input.open("in12.data");
    string line;
    char command;
    int value;

    int npos = 0;
    int epos = 0;

    int wnpos = 1;
    int wepos = 10;

    while(getline(input,line)){
        command = line[0];
        value = stoi(line.substr(1));

        /*
        if (command == 'N') npos+=value;
        else if (command == 'S') npos-=value;
        else if (command == 'W') epos-=value;
        else if (command == 'E') epos+=value;
        else if (command == 'L') {heading-=value;}
        else if (command == 'R') {heading+=value;}
        else if (command == 'F'){
            while (heading<0) heading+=360;
            while (heading>=360) heading-=360;
            if (heading == 0) npos+=value;
            else if (heading == 90) epos+=value;
            else if (heading == 180) npos-=value;
            else if (heading == 270) epos-=value;
        }*/

        if (command == 'N') wnpos+=value;
        else if (command == 'S') wnpos-=value;
        else if (command == 'W') wepos-=value;
        else if (command == 'E') wepos+=value;
        else if (command == 'L') {
            int tempe,tempn;
            value*=-1;
            tempn = round(cos(value*pi/180))*wnpos - round(sin(value*pi/180))*wepos;
            tempe = round(sin(value*pi/180))*wnpos + round(cos(value*pi/180))*wepos;
            wnpos = tempn;
            wepos = tempe;
        }else if (command == 'R') {
            int tempe,tempn;
            tempn = round(cos(value*pi/180))*wnpos - round(sin(value*pi/180))*wepos;
            tempe = round(sin(value*pi/180))*wnpos + round(cos(value*pi/180))*wepos;
            wnpos = tempn;
            wepos = tempe;
        }
        else if (command == 'F'){
            npos += wnpos*value;
            epos += wepos*value;
        }
        cout << npos << " x " << epos  << " wp : " <<  wnpos << " x " << wepos << endl;
    }

    cout << npos << " " << epos << endl;
    cout << abs(npos) + abs(epos) << endl;



    return 0;
}