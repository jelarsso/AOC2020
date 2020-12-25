#include<iostream>
#include<string>
#include<fstream>
#include<regex>

using namespace std;


unsigned long long int evaluate_inner_expr(string expr){
    regex re("\\d+");
    smatch matches;
    unsigned long long int a;
    bool op;
    if (expr.find('+')<expr.find('*')) {a=0;}
    else if (expr.find('+')>expr.find('*')) {a=1;}
    else return 0;


    while(regex_search(expr, matches, re)){
        for (string inner_expr:matches){

            if (expr.find('+')<expr.find('*')){op = true;}
            else if (expr.find('+')>expr.find('*'))  {op = false;}

            if (op) a+=stoll(inner_expr);
            else a*=stoll(inner_expr);
        }
        
        expr = matches.suffix().str();    
    }
    return a;
}


unsigned long long int evaluate_inner_expr2(string expr){
    regex add("\\d+ \\+ \\d+");
    regex nr("\\d+");
    smatch matches;
    unsigned long long int a = 1;
    string number;

    if (expr.length()<=1) return 0;

    while(regex_search(expr, matches, add)){
        for (string inner_expr:matches){
            int opindx = inner_expr.find('+');
            number = to_string( stoll(inner_expr.substr(0,opindx)) + stoll(inner_expr.substr(opindx+1)) );
        }
        expr = matches.prefix().str() + number +  matches.suffix().str();
    }
    smatch matches2;
    while (regex_search(expr,matches2,nr)){
        for (string inner_expr:matches2){
            a*=stoll(inner_expr);
        }
        expr = matches2.suffix().str();
    }
   
    return a;
}


unsigned long long int evaluate(string expr){
    regex re("\\((([^()]+))*\\)");
    smatch matches;
    string replace;
    while(regex_search(expr, matches, re)){
        for (string inner_expr:matches){
            replace = to_string(evaluate_inner_expr2(inner_expr));

        }
        expr = matches.prefix().str() +  replace + matches.suffix().str();
    }
    cout << expr << endl;
    return evaluate_inner_expr2(expr);
}


int main(){//could be parallellized
    
    
    ifstream input_file("in18.data");
    unsigned long long int sum = 0;
    string expr;
    

    while(getline(input_file,expr)){
        cout << expr << endl;
        sum += evaluate(expr);
        cout << sum << endl;
    }
    


    return 0;
}