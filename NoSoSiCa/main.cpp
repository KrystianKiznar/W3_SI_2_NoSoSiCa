#include<iostream>
#include<string>
#include<stack>
using namespace std;
stack<char> my_stack;
string operators{ "+-*/" };


string ConvertOperationIntoNotation(string operation) {
	//takes operatnion and convert it into RPN notation. A+B*C-D ==> ABC*+D- 
	string notation{};
	for (auto x : operation) {
		if (x >= '0' && x <= '9')
			notation += x;
		else if (!my_stack.size() == 0) {
			if (operators.find(x) > operators.find(my_stack.top()))
			{
				my_stack.push(x);
			}
			else
			{
				while (!my_stack.empty())
				{
					notation += my_stack.top();
					my_stack.pop();
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

int main() {

	string operation{ "4*4+3/2" };
	string notation{};

	notation = ConvertOperationIntoNotation(operation);
	cout << "For " << operation << " notation is: " << notation << endl;
	return 0;
}