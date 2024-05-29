#include <iostream>
#include <vector>
#include <stack>
#include <cctype>
#include <string>
#include <cmath>

using namespace std;

bool isOperator(char op){
    return op == '+' || op == '-' || op == '*' || op == '/' || op == '%';
}

vector<string> stringToInfix(string str){
    vector<string> infix;
    string angka;

        for (size_t i = 0; i< str.size(); i++){
            char ch = str[i];

            if(isspace(ch)){
                continue;
            }else if(isdigit(ch) || ch == '.'){
                angka += ch;
            }else if(ch == '-' && (i == 0 || isOperator(str[i-1]))){
                if(isOperator(str[i-1]) || str[i+1] == '('){
                    infix.push_back("-1");
                    infix.push_back("*");
                }else{
                    angka += ch;
                }
            }else {
                if(!angka.empty()){
                infix.push_back(angka);
                angka.clear();
            }
            infix.push_back(string(1, ch));
        }
    }
    if(!angka.empty()){
        infix.push_back(angka);
    }
    return infix;
}

void printElemen(const vector<string>& infix){
    for(size_t i = 0; i < infix.size(); i++){
        cout << infix[i] << " ";
    }
    cout << endl;
}
int main(){
    string infix;
    getline(cin, infix);

    vector<string> Parsingtoinfix = stringToInfix(infix);
    printElemen(Parsingtoinfix);
    return 0;
}