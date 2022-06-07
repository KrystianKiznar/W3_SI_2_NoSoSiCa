#include<iostream>
#include<string>
#include<stack>
using namespace std;
stack<char> my_stack;
string operators{ "+-*/" };


//bool IsDigit(char element)
//{
//	return element >= '0' && element <= '9';
//}
//
//int str_to_int(string a, int& poz)
//{
//	int liczba = 0;
//	while (poz < a.size() && IsDigit(a[poz]))
//	{
//		//schemat Hornera
//		liczba = liczba * 10 + a[poz] - '0';
//		++poz;
//	}
//	--poz;
//	return liczba;
//}

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
		return a / b;//dzielenie calkowite
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

int Calculate(string notation) {
	int result;

	for (auto x : notation) {
		int value_a, value_b;
		if (x >= '0' && x <= '9')
			my_stack.push(x - 48);

		else {
			int out;
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

	string operation{ "4*4+3/3" };
	string notation{};
	int result;

	notation = ConvertOperationIntoNotation(operation);
	result = Calculate(notation);
	cout << "For " << operation << " notation is: " << notation << endl;
	cout << "For this " << operation << " the output is " << result << endl;

	return 0;
}