#include <iostream>
#include <stack>
#include <string>

using namespace std;

int longestSubstring(string const& str) {
	stack<int> s;
	s.push(-1);

	// Тук си пазим най-дългия валиден подниз на обходения до момента низ
	int longestSubstr = 0;
	
	for (int i = 0; i < str.size(); i++) {
		// Ако срещнем отваряща скоба, записваме позицията ѝ в стека
		if (str[i] == '(')
			s.push(i);

		if (str[i] == ')') {
			// Изтриваме позицията на последната отваряща, която отговаря на
			// текущата затваряща.
			s.pop();

			// Ако стекът не е празен, сме във валиден подниз и обновяваме стойността
			// на longestSubstr
			if (!s.empty())
				longestSubstr = max(longestSubstr, i - s.top());
			
			// Ако стекът е празен, то тази затваряща скоба не е част от валиден подниз,
			// но е възможно следващата скоба да е отваряща и да е начало на валиден подниз.
			else
				s.push(i);
		}
	}
	
	return longestSubstr;
}

int main() {
	cout << longestSubstring(")()())") << endl;
	cout << longestSubstring("())))))") << endl;
	cout << longestSubstring("(()()))") << endl;
	cout << longestSubstring("))))()))))") << endl;
}
