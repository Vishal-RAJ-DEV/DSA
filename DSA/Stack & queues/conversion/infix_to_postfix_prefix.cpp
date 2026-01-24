#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
given : infix expression : a+b*(c^d-e)^(f+g*h)-i
output : postfix expression : abcd^e-fgh*+^*+i-
output : prefix expression : -+a*b^-^cd e +f*gh
*/

int precedence( char op){
    if( op == '^') return 3;
    else if ( op == '*' || op == '/') return 2;
    else if( op == '+' || op == '-') return 1;
    else return 0;

}

int infixToPostfix(string infix){
    stack<char> s ;
    string postfix  = "";
    int i = 0 ;
    while( i < infix.length()){
        char curr =  infix[i];
        if( ( curr >= 'a' && curr <= 'z') ||
            ( curr >= 'A' && curr <= 'Z') ||
            ( curr >= '0' && curr <= '9'))
            {
                postfix += curr;
        }

        else if( curr == '('){
            s.push( curr);
        }
        // if closing bracket is found then pop until opening bracket is found and add the operators to postfix
        else if ( curr == ')'){
            while( !s.empty() && s.top() != '('){
                postfix += s.top();
                s.pop();
            }
            if(!s.empty()) s.pop(); // pop the opening bracket
        }

        else{ //operator is found and either add to the stack or pop the higher precedence operators from stack and add to postfix
            while( !s.empty() && precedence(s.top()) >= precedence( curr)){
                postfix += s.top();
                s.pop();
            }
            s.push(curr);
        }
        i++;
    }
    
    while(!s.empty()){ //pop all the remaining operators
        postfix += s.top();
        s.pop();
    }
    cout << "Postfix Expression: " << postfix << endl;
    return 0;
}

int infixTOprefix(string infix){
    reverse(infix.begin(), infix.end()); //reverse the infix expression so that we can apply infix to postfix logic

    stack<char> s ;
    string postfix  = "";
    int i = 0 ;
    while( i < infix.length()){
        char curr =  infix[i];
        if( ( curr >= 'a' && curr <= 'z') ||
            ( curr >= 'A' && curr <= 'Z') ||
            ( curr >= '0' && curr <= '9'))
            {
                postfix += curr;
        }

        else if( curr == '('){
            s.push( curr);
        }
        // if closing bracket is found then pop until opening bracket is found and add the operators to postfix
        else if ( curr == ')'){
            while( !s.empty() && s.top() != '('){
                postfix += s.top();
                s.pop();
            }
            if(!s.empty()) s.pop(); // pop the opening bracket
        }

        else{ //operator is found and either add to the stack or pop the higher precedence operators from stack and add to postfix
            while( !s.empty() && precedence(s.top()) >= precedence( curr)){
                postfix += s.top();
                s.pop();
            }
            s.push(curr);
        }
        i++;
    }
    
    while(!s.empty()){ //pop all the remaining operators
        postfix += s.top();
        s.pop();
    }
    reverse(postfix.begin(), postfix.end()); //reverse the postfix to get prefix
    cout << "Prefix Expression: " << postfix << endl;
    return 0;
}

int main(){
    string infix = "a+b*(c^d-e)^(f+g*h)-i";
    cout<<"Enter Infix Expression: ";
    cout<<infix<<endl;
    infixToPostfix(infix);

    infixTOprefix(infix);


    return 0;
}
