#include <stack>
#include <iostream>

using namespace std;

template <typename T>
class Queue {
	stack<T> s;

public:
	Queue();

	void enqueue(T const&);
	void dequeue();
	void print();
};

template <typename T>
Queue<T>::Queue() {
}

template <typename T>
void Queue<T>::enqueue(T const& elem) {
	s.push(elem);
}

template <typename T>
void Queue<T>::dequeue() {
	stack<T> temp;
	
	while(!s.empty()) {
		temp.push(s.top());
		s.pop();
	}
	
	temp.pop();
	
	while(!temp.empty()) {
		s.push(temp.top());
		temp.pop();
	}
}

template <typename T>
void Queue<T>::print() {
	stack<T> temp;
	
	while(!s.empty()) {
		temp.push(s.top());
		s.pop();
	}
	
	while(!temp.empty()) {
		T top = temp.top();
		cout << top << " ";
		s.push(top);
		temp.pop();
	}
}

int main() {
	Queue<int> q;
	
	for (int i = 0; i < 10; i++)
		q.enqueue(i);
	
	q.print();
}