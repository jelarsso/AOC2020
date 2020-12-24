#include<iostream>
#include<fstream>
#include<string>
#include<regex>
#include<list>
#include<set>
using namespace std;


void find_combination(vector<set<int>>::iterator start, vector<set<int>> valids, vector<int> field_map){

    if (field_map.size()==20){
        cout << "success!" << endl;
        return;
    }

    if (field_map.size()==2) cout << field_map.back() << endl;
    for (set<int>::iterator it=start->begin(); it!=start->end(); ++it){
        cout << "trying number = " << *it << " " << field_map.size() << endl;
        for (vector<int>::iterator itv = field_map.begin(); itv!=field_map.end(); ++itv){
            if (*it == *itv){
                return;
            }
        }
        field_map.push_back(*it);
        find_combination(++start, valids, field_map);
        field_map.pop_back();
    }

};


bool cmp(pair<int,set<int>> i, pair<int,set<int>> j){
    return( i.second.size() < j.second.size());
};

int main(){

    ifstream input_ranges("in16ranges.data");
    string line;
    regex range_regex(R"(\d+-\d+)");
    smatch match;

    list<pair<int,int>> ranges;

    while (getline(input_ranges,line)){
        while(regex_search(line,match,range_regex)){
            for (string this_range:match){
                cout << this_range << endl;
                string low = this_range.substr(0,this_range.find('-'));
                string high = this_range.substr(1+this_range.find('-'),this_range.length()-this_range.find('-'));
                ranges.push_back(pair<int,int>(stoi(low),stoi(high)));
            }
        line = match.suffix().str();
        }
    }


    input_ranges.close();

    ifstream input_tickets("in16tickest.data");
    string valid_line;
    regex number_regex(R"(\d+)");
    line.clear();
    smatch match2,match3;
    bool is_number_valid,is_line_valid;
    int invalid_sum = 0;
    int valids = 0;
    string myticket;
    
    vector<set<int>> not_valid_fiels(20); // [index on ticket] yields a set of the ranges that does not fit this field on the tickect
    
    
    bool mytckt = true;
    while (getline(input_tickets,line)){
        if (mytckt){
            myticket = line;
            mytckt = false;
        }
        valid_line = line;
        is_line_valid = true;
        while(regex_search(line,match2,number_regex)){
            for (string this_number:match2){
                is_number_valid = false;
                int number = stoi(this_number);
                for (list<pair<int,int>>::iterator it = ranges.begin(); it!=ranges.end(); ++it){
                    if (it->first <= number && it->second >= number){
                        is_number_valid = true;
                        break;
                    }
                }
                if (!is_number_valid) {
                    //cout << number << endl;
                    is_line_valid = false;
                    invalid_sum += number;
                }
            }
        line = match2.suffix().str();
        }
        if (!is_line_valid){
            continue;
        }

        int ticket_index = 0;
        while(regex_search(valid_line,match3,number_regex)){
            for (string this_number:match3){
                is_number_valid = false;
                int number = stoi(this_number);
                int range_index = 0;
                for (list<pair<int,int>>::iterator it = ranges.begin(); it!=ranges.end(); advance(it,2)){
                    if ( (it->first > number || it->second < number) && ( (next(it))->first > number || (next(it))->second < number) ) not_valid_fiels[ticket_index].insert(range_index/2);
                    range_index+=2;
                }
            }
        ticket_index++;
        valid_line = match3.suffix().str();
        }
    }

    
    vector<set<int>> valid_numbers(20);
    
    for(int i = 0; i<20; i++){
        for(int j = 0; j<20; j++){
            valid_numbers[i].insert(j);
        }
    }

    int i = 0;
    for(vector<set<int>>::iterator it = not_valid_fiels.begin(); it!=not_valid_fiels.end(); ++it){
        
        for(set<int>::iterator it2 = it->begin(); it2!=it->end(); ++it2){

            for(set<int>::iterator it3 = valid_numbers[i].begin(); it3!=valid_numbers[i].end(); ++it3){
                if (*it3 == *it2){
                    it3 = valid_numbers[i].erase(it3);
                }
            }
        }
        i++;
    }

    vector<pair<int,set<int>>> numbers_and_indx(20);
    i = 0;
    for(vector<set<int>>::iterator it = valid_numbers.begin(); it!=valid_numbers.end(); ++it){
        numbers_and_indx[i] = pair<int,set<int>>(i,*it);
        i++;
    }



    sort(numbers_and_indx.begin(),numbers_and_indx.end(), cmp);
    vector<int> seen;
    for(vector<pair<int,set<int>>>::iterator it = numbers_and_indx.begin(); it!= numbers_and_indx.end(); ++it){
        seen.push_back(*(it->second.begin()));
        
        for (vector<pair<int,set<int>>>::iterator it2 = next(it); it2!=numbers_and_indx.end(); ++it2){
            for(vector<int>::iterator it3 = seen.begin(); it3!=seen.end(); it3++){
                
                for(set<int>::iterator it4 = it2->second.begin(); it4!=it2->second.end(); ++it4){
                    if(*it4 == *it3){
                        it4 = it2->second.erase(it4);
                    }
                }
                
            }
        }
    }

    for(vector<pair<int,set<int>>>::iterator it = numbers_and_indx.begin(); it!= numbers_and_indx.end(); ++it){
        cout << it->first << " ";
        for (set<int>::iterator it2 = it->second.begin(); it2!=it->second.end(); ++it2){
            cout << *it2 << " ";
        }
        cout << endl;

    }
    smatch match4;
    vector<int> my_ticket;
    while(regex_search(myticket,match4,number_regex)){
            for (string this_number:match4){
                int number = stoi(this_number);
                my_ticket.push_back(number);
            }
        myticket = match4.suffix().str();
    }
    long int answer = 1;
    vector<pair<int,set<int>>>::iterator ticket = numbers_and_indx.begin();
    for (vector<int>::iterator it = seen.begin(); it!=seen.end(); ++it){
        //cout << "ticket = " << ticket->first << " range = " <<  *it << endl;
        if (*(ticket->second.begin()) <= 5){
            answer *= my_ticket[ticket->first];
            cout << ticket->first << " " << *it << " " << my_ticket[ticket->first] << endl;
            //cout << my_ticket[*it] << endl;
        }
        ++ticket;

    }
    
    cout << answer << endl;

    return 0;
}