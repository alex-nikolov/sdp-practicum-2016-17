#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool correctParentheses(string const& str) {
	// Всъщност стекът може да е от какъвто тип си искаме,
	// дори можем да минем без стек, а само с брояч.
	stack<char> s;
	
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '(')
			s.push('(');

		if (str[i] == ')') {
			if (s.empty())
				return false;
			else
				s.pop();
		}
	}
	
	return s.empty();
}

int main() {
	cout << correctParentheses("()") << endl;
	cout << correctParentheses("(()(()))") << endl;
	cout << correctParentheses("(((())))") << endl;
	cout << correctParentheses("(()()())") << endl;

	cout << correctParentheses(")") << endl;
	cout << correctParentheses("(") << endl;
	cout << correctParentheses("(()") << endl;
	cout << correctParentheses(")(") << endl;
}
