#include <iostream>
#include <stack>
#include <string>

using namespace std;

double applyOp(char op, double first, double second)
{
	switch (op) {
		case '+':
			return first + second;
		case '-':
			return first - second;
		case '*':
			return first * second;
		case '/':
			return first / second;
	}
}

// Взима последните 2 стойности от стека със стойности и прилага върху тях
// последната операция от стека с операции.
void evaluateLastTwo(stack<double>& values, stack<char>& ops) {
	// Обърнете внимание, че първо е вторият операнд, след това е първият.
	double second = values.top();
	values.pop();

	double first = values.top();
	values.pop();

	char op = ops.top();
	ops.pop();

	values.push(applyOp(op, first, second));
}

// Връща дали вторият оператор има по-голям или равен приоритет от първия
bool hasPrecedence(char firstOp, char secondOp)
{
	if (secondOp == '(' || secondOp == ')')
		return false;
	if ((firstOp == '*' || firstOp == '/') && (secondOp == '+' || secondOp == '-'))
		return false;
	return true;
}

// Същинската функция в задачата
double evaluate(string const& expression)
{
	// Ще си пазим числата и операторите в два стека.
	stack<double> values;
	stack<char> ops;

	for (int i = 0; i < expression.size(); i++)
	{
		// Малка добавка, за да работи програмата ни за по-подредени стрингове.
		if (expression[i] == ' ')
			continue;

		// Ако сме намерили число, го слагаме в стека за числа.
		if (expression[i] >= '0' && expression[i] <= '9')
			values.push(expression[i] - '0');

		// Ако сме намерили отваряща скоба, я слагаме в списъка с оператори.
		if (expression[i] == '(')
			ops.push(expression[i]);

		if (expression[i] == ')')
		{
			// При достигане на затваряща скоба сме достигнали край на
			// операция с най-висок приоритет, следователно можем да пресметнем
			// натрупаните до момента стойности докато не срещнем отварящата скоба.
			while (ops.top() != '(')
			    evaluateLastTwo(values, ops);

			// Накрая не забравяме да изтрием самата отваряща скоба.
			ops.pop();
		}

		if (expression[i] == '+' || expression[i] == '-' ||
			expression[i] == '*' || expression[i] == '/')
		{
			// Ако текущият ни операнд има по-малък или равен приоритет
			// от последния оператор в стека, можем спокойно да извършим действието.
			while (!ops.empty() && hasPrecedence(expression[i], ops.top()))
				evaluateLastTwo(values, ops);

			// Не забравяме да добавим новия оператор в стека.
			ops.push(expression[i]);
		}
	}

	// Възможно е да има останали непресметнати данни.
	while (!ops.empty())
		evaluateLastTwo(values, ops);

	// Резултатът от пресмятането е записан във върха на стека.
	return values.top();
}

int main() {
	cout << evaluate("(5+6)*2") << endl;
	cout << evaluate("1+3*5+2") << endl;
	cout << evaluate("(1+3)*(5+2)") << endl;
	cout << evaluate("5+6-7+1") << endl;
	cout << evaluate("7/1-7/2") << endl;
}
