#include "my_stack.h"

MyStack::MyStack() {
}

void MyStack::push(double value) {
	q.push(value);
}

double MyStack::pop() {
	// Един вариант за решение е да минем през цикъл size - 1 пъти
	// и при всяка итерация да преместим текущия първи елемент най-отзад.
	// Така си гарантираме, че първоначално последният елемент ще стане първи
	// и можем лесно да го изтрием, запазвайки реда на останалите елементи в опашката.
	//
	// Примерче:
	// 1 2 3 10
	// 
	// След първа итерация:
	// 2 3 10 1
	//
	// След втора итерация:
	// 3 10 1 2
	//
	// След трета итерация:
	// 10 1 2 3
	for (int i = 0; i < q.size() - 1; i++) {
		int temp = q.front();
		q.pop();
		q.push(temp);
	}

	// Не е задължително да връщате изтритата стойност.
	int toPop = q.front();
	q.pop();
	
	return toPop;
}

bool MyStack::empty() const {
	return q.empty();
}

int MyStack::size() const {
	return q.size();
}