#include <iostream>
#include <list>
#include <cmath>

using namespace std;

void listMinMax(list<double> const& li, double& min, double& max) {
	if (li.empty())
		return;

	int tempMin = li.front();
	int tempMax = li.front();

	// Обърнете внимание на const, тъй като подаваме списъка като const&
	for (list<double>::const_iterator it = li.begin(); it != li.end(); it++) {
		if (tempMin > *it)
			tempMin = *it;
		if (tempMax < *it)
			tempMax = *it;
	}
	
	min = tempMin;
	max = tempMax;
}

void reverse(list<double>& li) {
	// Както при масивите, ще обхождаме до средата и ще си пазим текущи позиции в двата края на списъка,
	// които ще се приближават на всяка итерация на цикъла, и ще разменяме текущите елементи
	list<double>::iterator left = li.begin();
	list<double>::reverse_iterator right = li.rbegin();
	
	for (int i = 0; i < li.size() / 2; i++) {
		swap(*left, *right);
		left++;
		right++;
	}
}

int listToBinary(list<int> const& li) {
	int total = 0;
	int i = 0;

	// Отново const, понеже подаваме const&
	for (list<int>::const_reverse_iterator it = li.rbegin(); it != li.rend(); it++)
		total += *it * pow(2, i++);

	return total;
}

// Сложност: O(n)
void sortAbsSorted(list<double>& li) {
	// Идеята е да обходим списъка отляво надясно и ако видим елемент по-малък от нула,
	// го слагаме най-отпред и го трием от текущата му позиция.
	// Тук съществено използваме факта, че елементите на списъка са сортирани по абсолютна стойност,
	// тъй като колкото по-надясно открием отрицателно число, то толкова му е по-голяма абсолютната стойност
	// и съответно толкова по-напред трябва да седи в списъка.
	// Примерче:
	//
	// Вход: -1 2 -5 6
	//        ^
	// След първа итерация: -1 2 -5 6
	//                         ^
	// След втора итерация: -1 2 -5 6
	//                            ^
	// След трета итерация: -5 -1 2 6
	//                              ^
	// В цикъла премахваме обичайното it++, тъй като когато трием елемент от списъка,
	// останалите "запълват" дупката и итераторът вече сочи към следващия елемент,
	// т.е. е необходимо да го преместим само когато текущият елемент е положително число.
	// Примерче:
	// Преди erase: 1 2 3 4 5 6
	//                  ^
	// След erase:  1 2 4 5 6
	//                  ^
	for (list<double>::iterator it = li.begin(); it != li.end();) {
		if (*it < 0) {
			li.push_front(*it);
			it = li.erase(it);
		}
		else
			it++;
	}
}

// Сложност: O(nlgn)
void alternateSort(list<double>& li) {
    li.sort();

    list<double>::iterator it = li.begin();
	it++;
 
    for (int i = 1; i < (li.size() + 1) / 2; i++) {
        // Взимаме си последния елемент, който представлява следващия най-голям,
		// и го изтриваме.
        double nextBiggest = li.back();
        li.pop_back();

        // Изтриваме го след следващия минимален елемент.
		// В случая константно вмъкване, тъй като вече знаем къде да вмъкваме.
        li.insert(it, nextBiggest);

		it++;
    }
	// Примерче:
	// След сортировката: 1 2 3 4 5
	//                      ^
	// След първа итерация: 1 5 2 3 4
	//                            ^
	// След втора итерация: 1 5 2 4 3
	//                                ^
	// В случая insert вмкъва на предходната позиция, към която сочим.
	// Преди insert: 1 2 3 4 5
	//                   ^
	// След insert: 1 2 10 3 4 5
	//                     ^
}


int main() {
	list<double> li;

	li.push_back(-2);
	li.push_back(3);
	li.push_back(-5);
	li.push_back(-8);
	li.push_back(19);
	li.push_back(9);
	li.push_back(7);
	li.push_back(7);

	double min, max;
	alternateSort(li);
	
	for (list<double>::iterator it = li.begin(); it != li.end(); it++)
		cout << *it << " ";
}