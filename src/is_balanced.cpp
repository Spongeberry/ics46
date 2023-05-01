#include "is_balanced.h"


bool is_balanced(string s){
    stack<char> p_stack;
    for (char c : s){
        if (c == '(' || c == '[' || c == '{' || c == '<') {
            p_stack.push(c);
        } else if (c == ')' || c == ']' || c == '}' || c == '>') {
            if (p_stack.empty() || 
                (c == ')' && p_stack.top() != '(') ||
                (c == ']' && p_stack.top() != '[') ||
                (c == '}' && p_stack.top() != '{') ||
                (c == '>' && p_stack.top() != '<')) {
                return false;
            } else {
                p_stack.pop();
            }
        }
    }
    return p_stack.empty();
}

void error(string msg, char c){
    cout << c << msg << endl;
}

void test_is_balanced(){
    string test1 = "({(())})((([({})])))(((((<>([{()}])(<>))))))()";
    string test2 = "({(<>)})((([({})])))(((((()([{()}])(())))))";
    string test3 = "({(<>)})((([({})])))((((([]([{<>}])(()))))))()])";

    cout << "Test 1: " << (is_balanced(test1) ? "Balanced" : "Not Balanced") << endl;
    cout << "Test 2: " << (is_balanced(test2) ? "Balanced" : "Not Balanced") << endl;
    cout << "Test 3: " << (is_balanced(test3) ? "Balanced" : "Not Balanced") << endl;
}