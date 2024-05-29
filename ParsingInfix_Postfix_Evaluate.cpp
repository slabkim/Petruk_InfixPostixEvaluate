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

int Precedence(char op){
    if(op == '+' || op == '-') return 1;
    if(op == '*' || op == '/' || op == '%') return 2;
    return 0;
}

vector<string> strToInfix(string str){
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

vector<string> infixToPostfix(const vector<string>& infix){
    vector<string> postfix;
    stack<string> ops;

    for(const string& token : infix){
        if(isdigit(token[0]) || token[0] == '.' || (token.size()>1 && (isdigit(token[1]) || token[1] == '.'))){
            postfix.push_back(token);
        }else if(token == "("){
            ops.push(token);
        }else if(token == ")"){
            while (!ops.empty() && ops.top() != "("){
                postfix.push_back(ops.top());
                ops.pop();
            }
            if(!ops.empty()) ops.pop();
        }else if(isOperator(token[0])){
            while(!ops.empty() && Precedence(ops.top()[0]) >= Precedence(token[0])){
                postfix.push_back(ops.top());
                ops.pop();
            }
            ops.push(token);
        }
    }
    while(!ops.empty()){
        postfix.push_back(ops.top());
        ops.pop();
    }
    return postfix;
}

float evaluatePostfix(const vector<string>& postfix) {
    stack<float> values;
    for(const string& token : postfix) {
        if(isdigit(token[0]) || token[0] == '.' || (token.size() > 1 && (isdigit(token[1]) || token[1] == '.'))) {
        values.push(stof(token));
        }else if(isOperator(token[0])) {
        float b = values.top(); values.pop();
        float a = values.top(); values.pop();
        float result = 0;

        switch (token[0]) {
            case '+': result = a + b; break;
            case '-': result = a - b; break;
            case '*': result = a * b; break;
            case '/': result = a / b; break;
            case '%': result = fmod(a,b); break;
            }
            values.push(result);
        }
    }
    return values.top();
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

    vector<string> Parsingtoinfix = strToInfix(infix);
    cout << "infix: ";
    printElemen(Parsingtoinfix);

    vector<string> InfixtoPostfix = infixToPostfix(Parsingtoinfix);
    cout << "postfix: ";
    printElemen(InfixtoPostfix);

    float Evaluate = evaluatePostfix(InfixtoPostfix);
    cout << "hasil: "<<Evaluate << endl;

    return 0;
}
