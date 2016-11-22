#include <iostream>
#include <queue>
#include <string>

using namespace std;

void printBinaries(int n) {
	// Правим си опашка от стрингове и добавяме "1"
	queue<string> q;
	q.push("1");
	
	for (int i = 0; i < n; i++) {
		// Следващите числа в двоичен запис се получават като от текущото
		// най-малко добавим нула и единица най-отзад. Тези две нови числа
		// ги добавяме към опашката.
		string front = q.front();
		q.pop();
		cout << front << endl;

		q.push(front + "0");
		q.push(front + "1");
	}
}
/*
int main() {
	printBinaries(15);
}*/