//
//  eval.cpp
//  eval
//
//  Created by Haley Kim on 2/5/19.
//  Copyright © 2019 Haley Kim. All rights reserved.
//

#include "Set.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

// checking if infix is valid
bool isValid(string infix)
{
    // delete all space characters
    string newinfix = "";
    for (int i = 0; i < infix.size(); i++)
    {
        if (infix[i] != ' ')
            newinfix += infix[i];
    }
    infix = newinfix;
    // all must be letters or &,|,!,(,)
    for (int i = 0; i < infix.size(); i++)
    {
        if ((islower(infix[i]) == false) && (infix[i] != '!') && (infix[i] != '&') && (infix[i] != '|') && (infix[i] != '(') && (infix[i] != ')'))
            return false;
    }
    // if there are no operands, false
    int count = 0;
    for (int i = 0; i < infix.size(); i++)
    {
        if (islower(infix[i]))
            count++;
    }
    if (count == 0)
        return false;
    // if only one item or no item, false
    if (infix.size() == 0)
        return false;
    //    checking first char
    if ((infix[0] == '&') || (infix[0] == '|'))
        return false;
    if (infix.size() > 1)
    {
        if ((islower(infix[0]) == true) && (islower(infix[1]) == true))
        {
            return false;
        }
    }
    if ((islower(infix[0])) && (infix[1] == '('))
        return false;
    //    checking all middle chars
    if (infix.size() > 2)
    {
        for (int i = 1; i < infix.size()-1; i++)
        {
            // if & and | are next to each other, false
            if (((infix[i] == '&') && (infix[i-1] == '&')) || ((infix[i] == '&') && (infix[i-1] == '|')))
                return false;
            if (((infix[i] == '|') && (infix[i-1] == '&')) || ((infix[i] == '|') && (infix[i-1] == '|')))
                return false;
            if (((infix[i] == '&') && (infix[i+1] == '&')) || ((infix[i] == '&') && (infix[i+1] == '|')))
                return false;
            if (((infix[i] == '|') && (infix[i+1] == '&')) || ((infix[i] == '|') && (infix[i+1] == '|')))
                return false;
            // if ! is before a & or |
            if (((infix[i] == '&') && (infix[i-1] == '!')) || ((infix[i] == '|') && (infix[i-1] == '!')))
                return false;
            // if there is a letter next to a letter, false
            if ((islower(infix[i]) == true) && (islower(infix[i-1]) == true))
                return false;
            if ((islower(infix[i]) == true) && (islower(infix[i+1]) == true))
                return false;
            // if there's letters on both sides of exclamation mark, false
            if ((infix[i] == '!') && (islower(infix[i-1])) && (islower(infix[i+1])))
                return false;
            // if there is a paren next to a letter, false
            if ((islower(infix[i])) && (infix[i-1] == ')'))
                return false;
            if ((islower(infix[i])) && (infix[i+1] == '('))
                return false;
        }
    }
    //    checking last char
    if (infix.size() > 1)
    {
        if ((infix[infix.size()-1] == '&') || (infix[infix.size()-1] == '|') || (infix[infix.size()-1] == '!'))
            return false;
        if ((islower(infix[infix.size()-1])) && (infix[infix.size()-2] == ')'))
            return false;
    }
    // matching parens
    stack<char> parens;
    for (int i = 0; i < infix.size(); i++)
    {
        char a = infix[i];
        switch(a)
        {
            case '(':
                parens.push(a);
                break;
            case ')':
                parens.pop();
                break;
        }
    }
    if (!parens.empty())
        return false;
    // if none of these cases above happen, return true
    return true;
}

// determining precedence of operators
int precedence(char ch)
{
    switch(ch)
    {
        case '!':
            return '4';
        case '&':
            return '3';
        case '|':
            return '2';
        default:
            return '1';
    }
}

// convert infix to postfix
string convert(string infix, string& postfix)
{
    if (isValid(infix))
    {
    //    Initialize postfix to empty
        postfix = "";
    //    Initialize the operator stack to empty
        stack<char> operatorStack;
    //    For each character ch in the infix string
        for (int i = 0; i < infix.size(); i++)
        {
            char ch = infix[i];
            switch (ch)
            {
                case '!':
                case '(':
                    operatorStack.push(ch);
                    break;
                case ')':
                    while (operatorStack.top() != '(')
                    {
                        postfix += operatorStack.top();
                        operatorStack.pop();
                    }
                    operatorStack.pop();
                    break;
                case '&':
                case '|':
                    while (((!operatorStack.empty()) && (operatorStack.top() != '(')) && (precedence(ch) <= precedence(operatorStack.top())))
                    {
                        postfix += operatorStack.top();
                        operatorStack.pop();
                    }
                    operatorStack.push(ch);
                    break;
                case ' ':
                    break;
                default:
                    postfix += ch;
                    break;
            }
        }
        while (!operatorStack.empty())
        {
            postfix += operatorStack.top();
            operatorStack.pop();
        }
        return postfix;
    }
    return "This is not valid";
}

// evaluating postfix
int evaluate(string infix, const Set& trueValues, const Set& falseValues,
             string& postfix, bool& result)
{
    bool operand1;
    bool operand2;
    bool temp;
    if (isValid(infix) == 0)
        return 1;
    postfix = convert(infix, postfix);
    for (int i = 0; i < postfix.size(); i++)
    {
        if ((postfix[i] != '!') && (postfix[i] != '&') && (postfix[i] != '|'))
        {
            if ((trueValues.contains(postfix[i])) && (falseValues.contains(postfix[i])))
                return 3;
            if ((!trueValues.contains(postfix[i])) && (!falseValues.contains(postfix[i])))
                return 2;
        }
    }
    stack<bool> operandStack;
    for (int i = 0; i < postfix.size(); i++)
    {
        if ((postfix[i] != '!') && (postfix[i] != '&') && (postfix[i] != '|'))
        {
            if (trueValues.contains(postfix[i]))
                operandStack.push(true);
            else
                operandStack.push(false);
        }
        else if (postfix[i] == '!')
        {
            temp = operandStack.top();
            operandStack.pop();
            operandStack.push(!temp);
        }
        else
        {
            operand2 = operandStack.top();
            operandStack.pop();
            operand1 = operandStack.top();
            operandStack.pop();
            if (postfix[i] == '&')
            {
                if (operand1 && operand2)
                    operandStack.push(true);
                else
                    operandStack.push(false);
            }
            if (postfix[i] == '|')
            {
                if (operand1 || operand2)
                    operandStack.push(true);
                else
                    operandStack.push(false);
            }
        }
    }
    result = operandStack.top();
    return 0;
}
