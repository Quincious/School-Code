/** CS515 Assignment4
	File: evaluation.cpp
	Name: Jonathan Hart
	Section: 2
	Date: 9/29/13
	Collaboration Declaration: none
	*/


#include "stack.h"
#include <iostream>
#include <sstream>
using namespace std;

int priority(string str) {
    int retVal = 0;
    if (str == "*" || str == "/")
        retVal = 1;
    else  if (str == "+" || str == "-")
        retVal = 2;
    return retVal;
}

int main()
{
	string input;	

	cout <<  "Expression: ";
	
	while(getline(cin, input))
	{
		string outputQueue;
		stack evalStack;
		stack bracketStack;
		string str;
		stringstream ss(input);
		while(ss >> str)
		{
			if(str == "+" || str == "-" || 
				str == "/" || str == "*")
			{
				while (!evalStack.empty() && evalStack.top() != "(" && 
					evalStack.top() != "[" && evalStack.top() != "{" &&
					priority(evalStack.top()) <= priority(str)) 
				{
					outputQueue.append(evalStack.top() + " ");
					evalStack.pop();
				}

				evalStack.push(str);
			} 
			else if (str == "(" || str == "[" || str == "{") 
			{
				evalStack.push(str);
				bracketStack.push(str);

			} 
			else if (str == ")" || str == "]" || str == "}") 
			{
				while (evalStack.top() != bracketStack.top()) 
				{
					outputQueue.append(evalStack.top() + " ");
					evalStack.pop();
				}
				evalStack.pop();
				bracketStack.pop();
			} 
			else 
			{
				outputQueue.append(str + " ");
			}
		}

		while (!evalStack.empty()) 
		{
			outputQueue.append(evalStack.top() + " ");
			evalStack.pop();
		}

		stringstream ss2(outputQueue);

		while(ss2 >> str)
		{
			if(str == "+" || str == "-" || 
				str == "/" || str == "*")
			{
				if(evalStack.size() < 2)
				{
					cout << "Error! Not enough arguments for evaluation." << endl;
					return 0;
				}
				else
				{
					int firstNum;
					int secondNum;
					int result;
					stringstream buffer(evalStack.top());
					buffer >> secondNum;
					evalStack.pop();
					stringstream buffer2(evalStack.top());
					buffer2 >> firstNum;
					evalStack.pop();

					if(str == "+")
						result = firstNum + secondNum;
					else if(str == "-")
						result = firstNum - secondNum;
					else if(str == "*")
						result = firstNum * secondNum;
					else if(str == "/")
						result = firstNum / secondNum;

					buffer.clear();
					buffer << result;
					evalStack.push(buffer.str());
				}

			}
			else
			{
				evalStack.push(str);			
			}
		}
		
		cout << "Answer: " << evalStack.top() << endl;		
		cout <<  "Expression: ";
	}
	
	return 0;
}