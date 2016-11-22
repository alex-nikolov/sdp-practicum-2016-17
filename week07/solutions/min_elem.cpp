#include <queue>
#include <iostream>

using namespace std;

template <typename T>
T minElem(queue<T> q) {
	int size = q.size();
	T min = q.front();

	for (int i = 0; i < size; i++) {
		T front = q.front();

		if (min > front)
			min = front;

		q.pop();
		q.push(front);
	}

	return min;
}

int main() {
	queue<int> q;

	for (int i = 0; i < 10; i++)
		q.push(i);

	cout << minElem(q);
}
