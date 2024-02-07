// C++ program to convert infix to prefix

bool isOperator(char c)
{
	return (!isalpha(c) && !isdigit(c));
}

// Function to get the priority of operators
int getPriority(char C)
{
	if (C == '-' || C == '+')
		return 1;
	else if (C == '*' || C == '/')
		return 2;
	else if (C == '^')
		return 3;
	return 0;
}

// Function to convert the infix expression to postfix
string infixToPostfix(string infix)
{
	infix = '(' + infix + ')';
	int l = infix.size();
	stack<char> char_stack;
	string output;

	for (int i = 0; i < l; i++) {

		// If the scanned character is an
		// operand, add it to output.
		if (isalpha(infix[i]) || isdigit(infix[i]))
			output += infix[i];

		// If the scanned character is an
		// ‘(‘, push it to the stack.
		else if (infix[i] == '(')
			char_stack.push('(');

		// If the scanned character is an
		// ‘)’, pop and output from the stack
		// until an ‘(‘ is encountered.
		else if (infix[i] == ')') {
			while (char_stack.top() != '(') {
				output += char_stack.top();
				char_stack.pop();
			}

			// Remove '(' from the stack
			char_stack.pop();
		}

		// Operator found
		else {
			if (isOperator(char_stack.top())) {
				if (infix[i] == '^') {
					while (
						getPriority(infix[i])
						<= getPriority(char_stack.top())) {
						output += char_stack.top();
						char_stack.pop();
					}
				}
				else {
					while (
						getPriority(infix[i])
						< getPriority(char_stack.top())) {
						output += char_stack.top();
						char_stack.pop();
					}
				}

				// Push current Operator on stack
				char_stack.push(infix[i]);
			}
		}
	}
	while (!char_stack.empty()) {
		output += char_stack.top();
		char_stack.pop();
	}
	return output;
}

// Function to convert infix to prefix notation
string infixToPrefix(string infix)
{
	// Reverse String and replace ( with ) and vice versa
	// Get Postfix
	// Reverse Postfix
	int l = infix.size();

	// Reverse infix
	reverse(infix.begin(), infix.end());

	// Replace ( with ) and vice versa
	for (int i = 0; i < l; i++) {

		if (infix[i] == '(') {
			infix[i] = ')';
		}
		else if (infix[i] == ')') {
			infix[i] = '(';
		}
	}

	string prefix = infixToPostfix(infix);

	// Reverse postfix
	reverse(prefix.begin(), prefix.end());

	return prefix;
}

// Driver code
int main()
{
	string s = ("x+y*z/w+u");

	// Function call
	cout << infixToPrefix(s) << std::endl;
	return 0;
}
-------------------------------------------
// C++ Program to convert prefix to Infix
#include <iostream>
#include <stack>
using namespace std;

// function to check if character is operator or not
bool isOperator(char x) {
switch (x) {
case '+':
case '-':
case '/':
case '*':
case '^':
case '%':
	return true;
}
return false;
}

// Convert prefix to Infix expression
string preToInfix(string pre_exp) {
stack<string> s;

// length of expression
int length = pre_exp.size();

// reading from right to left
for (int i = length - 1; i >= 0; i--) {

	// check if symbol is operator
	if (isOperator(pre_exp[i])) {

	// pop two operands from stack
	string op1 = s.top(); s.pop();
	string op2 = s.top(); s.pop();

	// concat the operands and operator
	string temp = "(" + op1 + pre_exp[i] + op2 + ")";

	// Push string temp back to stack
	s.push(temp);
	}

	// if symbol is an operand
	else {

	// push the operand to the stack
	s.push(string(1, pre_exp[i]));
	}
}

// Stack now contains the Infix expression
return s.top();
}

// Driver Code
int main() {
string pre_exp = "*-A/BC-/AKL";
cout << "Infix : " << preToInfix(pre_exp);
return 0;
}
--------------------------------