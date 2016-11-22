#include <queue>
#include <iostream>
#include <numeric>
#include <sstream>
#include <algorithm>

using namespace std;

void helperPush(vector<int> const& arr, queue<int>& q, int i, int mod) {
	if (arr[i] % 3 == mod)
		q.push(arr[i]);
}

bool descSort(int a, int b) {
	return a > b;
}

int vectorToInt(vector<int> arr) {
	stringstream ss;

	for (int i = 0; i < arr.size(); i++)
		ss << arr[i];
	
	int res;
	ss >> res;
	return res;
}

void fillVectorFromQueue(vector<int>& arr, queue<int> q) {
	while (!q.empty()) {
		arr.push_back(q.front());
		q.pop();
	}
}

int calcMaxDivisable(queue<int> const& q0, queue<int> const& q1, queue<int> const& q2) {
	vector<int> res;

	fillVectorFromQueue(res, q0);
	fillVectorFromQueue(res, q1);
	fillVectorFromQueue(res, q2);

	sort(res.begin(), res.end(), descSort);
	return vectorToInt(res);
}

int maxDivisableByThree(vector<int> arr) {
	// Сортираме си масива от едноцифрени числа в нарастващ ред
	sort(arr.begin(), arr.end());

	// Създаваме си три опашки, в които ще пазим числата, които дават остатъци
	// 0, 1 и 2 при деление на 3.
	queue<int> q0;
	queue<int> q1;
	queue<int> q2;

	// Слагаме числата в съответните опашки
	for (int i = 0; i < arr.size(); i++) {
		helperPush(arr, q0, i, 0);
		helperPush(arr, q1, i, 1);
		helperPush(arr, q2, i, 2);
	}
	
	// Намираме сумата на елементите в масива.
	int sum = accumulate(arr.begin(), arr.end(), 0);
	
	cout << "sum: " << sum << endl;
	
	// Ако тя се дели на три, тогава може всички цифри да участват.
	// Най-голямо число ще се получи, когато сортираме цифрите в намаляващ ред.
	if (sum % 3 == 0) {
		sort(arr.begin(), arr.end(), descSort);
		return vectorToInt(arr);
	}
	// Ако тя дава остатък 1 при деление на 3, тогава ще пробваме да махнем елемент,
	// който дава остатък 1, така сумата на всички останали елементи ще се дели на 3.
	// Тук използваме опашката, за да подсигурим, че ще махнем възможно най-малкия
	// елемент, който дава остатък при деление 1. На практика двете опашки q1 и q2 могат
	// да се заменят с две двойки числа, които пазят двете най-малки цифри, които дават
	// остатък 1 и 2 при деление на 3.
	// Ако няма число, което е сравнимо с 1, тогава има две, които са сравними с 2, и в такъв случай
	// ги премахваме тях. Ако пък и двете условия са налице, трябва да изпълним първото (q1.pop),
	// тъй като така премахваме само 1 цифра и ще получим със сигурност по-голямо число,
	// отколкото ако премахнем две.
	if (sum % 3 == 1) {
		if (!q1.empty())
			q1.pop();
		else if (q2.size() > 1) {
			q2.pop();
			q2.pop();
		}
	}
	// Подобно разсъждение правим и ако сумата от цифрите дава остатък 2.
	if (sum % 3 == 2) {
		if (!q2.empty())
			q2.pop();
		else if (q1.size() > 1) {
			q1.pop();
			q1.pop();
		}
	}

	// Накрая сортираме цифрите в намаляващ ред.
	return calcMaxDivisable(q0, q1, q2);
}

int main() {
	vector<int> arr;
	
	arr.push_back(9);
	arr.push_back(5);
	arr.push_back(6);
	arr.push_back(9);
	
	cout << maxDivisableByThree(arr);
}