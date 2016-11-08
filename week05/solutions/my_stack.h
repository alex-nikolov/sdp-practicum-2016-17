#ifndef _MY_STACK
#define _MY_STACK

#include <queue>

class MyStack {
	private:
		std::queue<double> q;
	public:
		MyStack();
		
		void push(double);
		double pop();
		
		bool empty() const;
		int size() const;
};

#endif