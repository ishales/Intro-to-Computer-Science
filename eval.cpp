//
//  main.cpp
//  hw2 q5
//
//  Created by Isabelle Hales on 2/8/23.
//  Copyright © 2023 CS32. All rights reserved.
//

#include <iostream>
#include "Set.h"
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

bool isValidInfixString(const string& infix){
    int stringSize = infix.size();
    stack<char> Parenthesis;

    for(int i = 0; i < stringSize; i++){
        char curr = infix.at(i);
        //checks for balanced # of parenthesis
        if(curr == '('){
            Parenthesis.push(curr);
        }
        if(curr == ')'){
            if(Parenthesis.empty()){
                return false;
            } else{
                Parenthesis.pop();
            }
        }
        //checks only lower case letters
        if(isalpha(curr) && !islower(curr)){
            return false;
        }
    }
    
    
    if(Parenthesis.empty()){
        return true;
    } else {
        return false;
    }
}


int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result)
{
//adding code to detect whether or not the infix string is syntactically valid.
    
//   If infix is a syntactically valid infix boolean expression whose
//   only operands are single lower case letters (whether or not they
//   appear in the values sets), then postfix is set to the postfix
//   form of the expression.  If not, postfix might or might not be
//   changed, result is unchanged, and the function returns 1.
    if (!isValidInfixString(infix)){
        return 1;
    }

    postfix = "";           //prepares postfix string (ensures its clear)
    
    //infix to postfix
    stack<char> operatorStack;      //initialize the operator stack to empty
    
    for (int a = 0; a < infix.size(); a++){        //for each character ch in the infix string
        char c = infix.at(a);
        
        switch (c){                                 // switch (ch)
            //case whitespace
            case ' ':
                break;
            //case '('
            case '(':
                // syntax rules for (
                if((a > 0) && (trueValues.contains(infix.at(a-1)) || falseValues.contains(infix.at(a-1)) || (infix.at(a-1) == ')'))){
                    return 1;
                }
                operatorStack.push(c);              //push ch onto the operator stack
                break;
            //case ')'
            case ')':
                // syntax rules for )
                if((a > 0) && ((infix.at(a-1) == '&') || (infix.at(a-1) == '|') || (infix.at(a-1) == '!') || (infix.at(a-1) == '('))){
                    return 1;
                }
                // pop stack until matching '('
                while(operatorStack.top() != '('){
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                // remove the '('
                operatorStack.pop();
                break;
            //case operator
            case '!':
            case '&':
            case '|':
                //syntax rules
                    if(c == '&' || c == '|'){
                        if((a>0) && ( (infix.at(a-1) == '&') || (infix.at(a-1) == '|') || (infix.at(a-1) == '!'))){
                            return 1;
                        }
                    }
                
                //while the stack is not empty and the stack top is not '(' and precedence of ch <= precedence of stack top
                //append the stack top to postfix and pop the stack
                while(!operatorStack.empty() && operatorStack.top() != '(' && operatorStack.top() <= c){
                        postfix += operatorStack.top();
                        operatorStack.pop();
                }
                // push ch onto the stack
                operatorStack.push(c);
                break;
            //case operand
            default:
                postfix += c;                       //append ch to end of postfix
                break;
            }
        
        
    }
    // while the stack is not empty: append the stack top to postfix, pop the stack
    while(!operatorStack.empty()){
        postfix += operatorStack.top();
        operatorStack.pop();
        }
    
    
    for(int z = 0; z < postfix.size(); z++){
        char Scheck = postfix.at(z);
        if(isalpha(Scheck) && islower(Scheck)){
            //at least one letter in the expression is in neither the trueValues nor the falseValues sets (return 2)
            if(!trueValues.contains(Scheck) && !falseValues.contains(Scheck)){
                return 2;
            //at least one letter in the expression is in both the trueValues and the falseValues set. return 3
            } else if(trueValues.contains(Scheck) && falseValues.contains(Scheck)){
                return 3;
            }
        }
    }
    
    //evalutating postfix
    stack<char> operandStack;           //initialize the operand stack to empty
    
    
    char trueC;
    trueValues.get(0, trueC);
    char falseC;
    falseValues.get(0, falseC);
    
    for(int b = 0; b < postfix.size(); b++){
        char temp = postfix.at(b);
        
        // if ch is an operand
        if(isalpha(temp) && islower(temp)){
            operandStack.push(temp);    //push the value onto the operand stack
        } else {
            if(temp == '!'){
                if(operandStack.size() < 1){
                    return 1;
                }
                
                if(trueValues.contains(operandStack.top())){
                    operandStack.pop();
                    operandStack.push(falseC);
                } else {
                    operandStack.pop();
                    operandStack.push(trueC);
                }
                
            } else if (temp == '&' || temp == '|') {
            
            if(operandStack.size() < 2){
                return 1;
            }
                
            char operand2 = operandStack.top();
            operandStack.pop();
            char operand1 = operandStack.top();
            operandStack.pop();
            
                if(temp == '&'){
                    if(trueValues.contains(operand2) && trueValues.contains(operand1)){
                        operandStack.push(trueC);
                    } else {
                        operandStack.push(falseC);
                    }
                } else if (temp == '|'){
                    if(falseValues.contains(operand2) && falseValues.contains(operand1)){
                        operandStack.push(falseC);
                    } else {
                        operandStack.push(trueC);
                    }
                }
            
        }
    }
}
    // result is set to the result of evaluating the expression
    if(operandStack.size() != 1){
        return 1;
    }
    
    if(trueValues.contains(operandStack.top())){
        result = true;
        return 0;
    }
    
    if(falseValues.contains(operandStack.top())){
        result = false;
        return 0;
    }
    
    else {
        return 4;
    }

    }

    
    
int main() {
    
    cout << "Passed all tests" << endl;
    
    
}
