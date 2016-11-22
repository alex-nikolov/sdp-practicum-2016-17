#include <queue>
#include <iostream>

using namespace std;

int min(int a, int b, int c) {
	if (a > b)
		swap(a, b);
	if (a > c)
		swap(a, c);
	
	return a;
}

void popMin(queue<int>& q, int min) {
	if (q.front() == min)
		q.pop();
}

void hamming(int n) {
	cout << 1 << endl;

	// Създаваме си три опашки, в които ще пазим кратните на 2, 3 и 5.
	queue<int> two;
	queue<int> three;
	queue<int> five;
	
	two.push(2);
	three.push(3);
	five.push(5);
	
	for (int i = 1; i < n; i++) {
		// Взимаме си минималния елемент
		int minFront = min(two.front(), three.front(), five.front());
		
		cout << minFront << endl;
	
		// Изтриваме минималния елемент от съответната/ите опашка/и
		popMin(two, minFront);
		popMin(three, minFront);
		popMin(five, minFront);

		// Записваме числата на Хеминг, получени от нашето, с умножение на 2, 3 и 5
		two.push(2 * minFront);
		three.push(3 * minFront);
		five.push(5 * minFront);
	}
}
/*
int main() {
	hamming(50);
}*/
