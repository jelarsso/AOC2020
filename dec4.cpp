#include<fstream>
#include<iostream>
#include<string>
#include<regex>
using namespace std;


int check_date(string line, string val, int low, int high){
    regex e(".*"+val+"[1-2][0-9]{3}.*");
    int value = stoi(line.substr(line.find(val)+4,line.find(val)+8));
    if (value>=low && value<=high) {
        return 1;
    }
    return 0;
}

int check_height(string line){
    regex ecm(".*hgt:\\d{3}cm.*");
    regex ein(".*hgt:\\d{2}in.*");
    string substring = "";
    int hgt;
    int index = line.find("hgt:")+4;
    if (regex_match(line,ein)){    
        substring = line.substr(index,2);
        hgt = stoi(substring);
        return (hgt>=59 && hgt<=76);
    }else if (regex_match(line,ecm)){
        substring = line.substr(index,3);
        hgt = stoi(substring);
        return (hgt>=150 && hgt<=193);
    }
    return 0;
}

int check_hcl(string line){
    regex e(".*hcl:#[0-9a-f]{6}( .*|$)");
    return regex_match(line,e);
}

int check_ecl(string line){
    const char* ce[7] = {"ecl:amb", "ecl:blu", "ecl:brn", "ecl:gry", "ecl:grn", "ecl:hzl", "ecl:oth"};
    for (int i=0;i<7;i++){
        if (line.find(ce[i])<line.length()){
            return 1;
        }
    }
    return 0;
}


int check_pid(string line){
    regex e(".*pid:[0-9]{9}( .*|$)");
    return regex_match(line,e);
}


int main(){
    int fields_filled[7];
    for (int i=0;i<7;i++) fields_filled[i] = 0;
    int valid = 0;
    const char* field_names[7]={"byr:", "iyr:", "eyr:", "hgt:", "hcl:", "ecl:", "pid:"};



    ifstream input;

    input.open("in04.data");
    string line;

    if (input.is_open()){
        while(getline(input,line)){
            cout << line << endl;
            if (line.length()==0){
                int valid_fields = 0;
                for (int i=0;i<7;i++){ 
                    cout << fields_filled[i] << " ";
                    valid_fields += fields_filled[i];
                    };
                    cout << endl << endl << endl << endl;
                if (valid_fields==7) valid++;
                for (int i=0;i<7;i++) fields_filled[i] = 0;
                continue;
            }
            for (int i = 0; i<7; i++){
                if (line.find(field_names[i])<line.length()){
                    if (i == 0){
                    fields_filled[i] = check_date(line,field_names[i],1920,2002);
                    }else if (i == 1){
                    fields_filled[i] = check_date(line,field_names[i],2010,2020);
                    }else if (i == 2){
                    fields_filled[i] = check_date(line,field_names[i],2020,2030);
                    }else if (i == 3){
                    fields_filled[i] = check_height(line);
                    }else if (i == 4){
                    fields_filled[i] = check_hcl(line);
                    }else if (i == 5){
                    fields_filled[i] = check_ecl(line);
                    }else if (i == 6){
                    fields_filled[i] = check_pid(line);
                    }
                }
            }
                
        }
    }
    cout << valid << endl;
    input.close();
    return 0;
}