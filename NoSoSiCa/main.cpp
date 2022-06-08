#include<iostream>
#include<string>
#include<stack>
using namespace std;
stack<char> my_stack;
string operators{ "/*+-" };


int GetOperatorsWage(char oper) {

	switch (oper)
	{
	case '+':
		return 1;
	case '-':
		return 1;
	case '*':
		return 2;
	case '/':
		return 2;
	case '^':
		return 3;
	}
	cout << "Unexpected sign!";
	return 0;
}

int MakeCalculation(int a, int b, char oper)
{
	switch (oper)
	{
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		return a / b;
	case '^':
		return pow(a, b);
	}
	cout << "Unexpected sign!";
	return 0;
}

string ConvertOperationIntoNotation(string operation) {
	//takes operatnion and convert it into RPN notation. A+B*C-D ==> ABC*+D- 
	string notation{};
	for (auto x : operation) {
		if (x >= '0' && x <= '9')
			notation += x;
		else if (!my_stack.size() == 0) {
			if (GetOperatorsWage(x) > GetOperatorsWage(my_stack.top()))
			{
				my_stack.push(x);
			}
			else
			{
				while ((my_stack.size() != 0) && GetOperatorsWage(x) <= GetOperatorsWage(my_stack.top()))
				{
					if (!my_stack.size() == 0) {
						notation += my_stack.top();
						my_stack.pop();
					}	
					else
						break;
				}
				my_stack.push(x);
			}

		}
		else
			my_stack.push(x);
	}
	
	while (!my_stack.empty()) {
		notation += my_stack.top();
		my_stack.pop();
	}

	return notation;
}

int Calculate(string notation) {

	for (auto x : notation) {
		int value_a, value_b;
		if (x >= '0' && x <= '9')
			my_stack.push(x - 48);

		else {

			value_b = my_stack.top();
			my_stack.pop();
			value_a = my_stack.top();
			my_stack.pop();

			my_stack.push(MakeCalculation(value_a, value_b, x));
		}
	}
	return my_stack.top();
}


int main() {

	string operation{ "2+5*3+5^2" };
	string notation{};
	int result;

	notation = ConvertOperationIntoNotation(operation);
	result = Calculate(notation);
	cout << "For " << operation << " notation is: " << notation << endl;
	cout << "For this " << operation << " the output is " << result << endl;
	
	return 0;
}