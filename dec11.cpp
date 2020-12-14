#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class SeatSimulator{
    private:
    int width, length;
    int tolerancy = 5;
    char **seat_array;
    char **next_array;

    public:
    SeatSimulator(string filename){
        //initialize class from filename
        ifstream input;
        input.open(filename);
        string line;
        length = 0;
        while(getline(input, line)){
            width = line.length();
            length++;
        }
        cout << width << " by " << length << endl;
        seat_array = new char*[length];
        next_array = new char*[length];
        for (int i = 0;i<length; i++){
            seat_array[i] = new char[width];
            next_array[i] = new char[width];
        }
        input.clear();
        input.seekg(0);
        int row = 0;
        while(getline(input, line)){
            for (int col=0;col<width;col++){
                seat_array[row][col] = line[col];
            }
            row++;
        }
        input.close();
    };

    ~SeatSimulator(){
        for (int i = 0;i<length; i++){
            delete [] seat_array[i];
        }
        delete [] seat_array;
    };

    void print(){
        for(int row = 0; row<length; row++){
            for(int col = 0; col<width; col++){
                cout << seat_array[row][col];
            }
            cout << endl;
        }
        cout << endl;
    };

    int occupied(){
        int n_occupied_seats = 0;
        for(int row = 0; row<length; row++){
            for(int col = 0; col<width; col++){
                if (seat_array[row][col]=='#') n_occupied_seats++;
            }
        }
        return n_occupied_seats;
    };

    char flip(int row, int col){
        if (seat_array[row][col]=='L'){
            for (int i =-1;i<=1;i++){
                if (row+i>length-1 || row+i<0) continue;
                for (int j=-1;j<=1;j++){
                    if(col+j>width-1 || col+j<0) continue;
                    if (i==0 && j==0) continue;
                    if (seat_array[row+i][col+j]=='#') return 'L';
                }
            }
            return '#';
        }else if (seat_array[row][col]=='#'){
            int occupied_neighs = 0;
            for (int i = -1;i <= 1;i++){
                if (row+i>length-1 || row+i<0) continue;
                for (int j = -1;j <= 1;j++){
                    if(col+j>width-1 || col+j<0) continue;
                    if (i==0 && j==0) continue;
                    if (seat_array[row+i][col+j]=='#') occupied_neighs++;
                }
            }
            if (occupied_neighs>=tolerancy) return 'L';
            else return '#';
        }
        return '.';
    };

    char flip_visible(int row, int col){
        if (seat_array[row][col]=='L'){
            for (int i =-1;i<=1;i++){
                for (int j=-1;j<=1;j++){
                    
                    if (i==0 && j==0) continue;
                    int distance = 1;
                    while(row+distance*i<length && row+distance*i>=0 && col+distance*j<width && col+distance*j>=0){
                        if (seat_array[row+distance*i][col+distance*j]=='#') return 'L';
                        else if (seat_array[row+distance*i][col+distance*j]=='L') break;
                        distance++;
                    }
                }
            }
            return '#';
        }else if (seat_array[row][col]=='#'){
            int occupied_neighs = 0;
            for (int i = -1;i <= 1;i++){
                for (int j = -1;j <= 1;j++){
                    if (i==0 && j==0) continue;
                    int distance = 1;
                    while(row+distance*i<length && row+distance*i>=0 && col+distance*j<width && col+distance*j>=0){
                        if (seat_array[row+distance*i][col+distance*j]=='#') {occupied_neighs++;break;}
                        else if (seat_array[row+distance*i][col+distance*j]=='L') break;
                        distance++;
                    }
                }
            }
            if (row == 7 && col == 8) cout << occupied_neighs << endl;
            if (occupied_neighs>=tolerancy) return 'L';
            else return '#';
        }
        return '.';
    };

    int simulate_step(){
        //Simulate one pass.
        int nflipped = 0;
        for(int row = 0; row<length; row++){
            for(int col = 0; col<width; col++){
                char flipped = flip_visible(row,col);
                next_array[row][col] = flipped;
                if (seat_array[row][col]!=flipped) nflipped++;
            }
        }
        for(int row = 0; row<length; row++){
            for(int col = 0; col<width; col++){
                seat_array[row][col] = next_array[row][col];
            }
        }
        return nflipped;
    }
};




int main(){

    SeatSimulator s("in11.data");
    cout << "There are " << s.occupied() << " occupied seats." << endl; 
    int nflipped = 1;
    s.print();
    while(nflipped!=0){
        nflipped = s.simulate_step();
    }
    cout << "There are " << s.occupied() << " occupied seats." << endl; 

    return 0;
}