// evalaute prefix with single digit

bool isOperand(char c)
{
	// If the character is a digit then it must
	// be an operand
	return isdigit(c);
}

double evaluatePrefix(string exprsn)
{
	stack<double> Stack;

	for (int j = exprsn.size() - 1; j >= 0; j--) {

		// Push operand to Stack
		// To convert exprsn[j] to digit subtract
		// '0' from exprsn[j].
		if (isOperand(exprsn[j]))
			Stack.push(exprsn[j] - '0');

		else {

			// Operator encountered
			// Pop two elements from Stack
			double o1 = Stack.top();
			Stack.pop();
			double o2 = Stack.top();
			Stack.pop();

			// Use switch case to operate on o1
			// and o2 and perform o1 Or o2.
			switch (exprsn[j]) {
			case '+':
				Stack.push(o1 + o2);
				break;
			case '-':
				Stack.push(o1 - o2);
				break;
			case '*':
				Stack.push(o1 * o2);
				break;
			case '/':
				Stack.push(o1 / o2);
				break;
			}
		}
	}

	return Stack.top();
}

// Driver code
int main()
{
	string exprsn = "+9*26";
	cout << evaluatePrefix(exprsn) << endl;
	return 0;
}
----------------------------------------
// evaluate prefix with multiple digits

double evaluatePrefix(string exprsn)
{
	stack<double> Stack;

	for (int j = exprsn.size() - 1; j >= 0; j--) {
	
		// if jth character is the delimiter ( which is
		// space in this case) then skip it
		if (exprsn[j] == ' ')
			continue;

		// Push operand to Stack
		// To convert exprsn[j] to digit subtract
		// '0' from exprsn[j].
		if (isdigit(exprsn[j])) {
		
			// there may be more than 
			// one digits in a number
			double num = 0, i = j;
			while (j > 0 && isdigit(exprsn[j]))
				j--;
			j++;

			// from [j, i] exprsn contains a number
			for (int k = j; k <= i; k++)
				num = num * 10 + double(exprsn[k] - '0');

			Stack.push(num);
		}
		else {

			// Operator encountered
			// Pop two elements from Stack
			double o1 = Stack.top();
			Stack.pop();
			double o2 = Stack.top();
			Stack.pop();

			// Use switch case to operate on o1
			// and o2 and perform o1 O o2.
			switch (exprsn[j]) {
			case '+':
				Stack.push(o1 + o2);
				break;
			case '-':
				Stack.push(o1 - o2);
				break;
			case '*':
				Stack.push(o1 * o2);
				break;
			case '/':
				Stack.push(o1 / o2);
				break;
			}
		}
	}

	return Stack.top();
}

// Driver code
int main()
{
	string exprsn = "+ 9 * 12 6";
	cout << evaluatePrefix(exprsn) << endl;
	return 0;

	// this code is contributed by Mohd Shaad Khan
}
------------------

