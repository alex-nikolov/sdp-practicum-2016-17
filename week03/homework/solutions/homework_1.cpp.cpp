#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void first() {
	string firstFile, secondFile;
	cin >> firstFile >> secondFile;

	ifstream first(firstFile.c_str());
	ifstream second(secondFile.c_str());
	ofstream output("first_result.txt");

	string firstFileString, secondFileString;
	double firstFileNumber, secondFileNumber;

	// Докато можем да четем и от двата файла
	while (first >> firstFileString >> firstFileNumber &&
		second >> secondFileString >> secondFileNumber) {
	if (firstFileNumber < secondFileNumber) {
		output << firstFileString << " " << firstFileNumber << " "
			   << secondFileString << " " << secondFileNumber << endl;
	}
	else
		output << secondFileString << " " << secondFileNumber << " "
			   << firstFileString << " " << firstFileNumber << endl;
	}

	// Ако двата файла имат еднакъв брой редове, край.
	if (second.eof() && first.eof())
		return;

	// Иначе, ако вторият има повече редове
	if (first.eof()) {
	// В момента в двете променливи стоят валидни данни от втория файл,
	// т.е. трябва първо да ги запишем
		output << secondFileString << " " << secondFileNumber << endl;

		while (second >> secondFileString >> secondFileNumber)
			output << secondFileString << " " << secondFileNumber << endl;
	}
	// В противен случай, т.е. ако вторият файл има повече редове
	else {
		output << firstFileString << " " << firstFileNumber << endl;

		while (first >> firstFileString >> firstFileNumber)
			output << firstFileString << " " << firstFileNumber << endl;
	}

	first.close();
	second.close();
	output.close();
}

void second() {
	ifstream input("second.txt");
	string line;
	string name;
	double iq;

	while (getline(input, line)) {
		// За улеснение приемаме, че след числото няма други интервали
		// Тази функция ще ви вземе позицията на последния интервал
		size_t lastSpace = line.find_last_of(" ");

		// name става тази част от line преди последното срещане на интервала
		name = line.substr(0, lastSpace);

		// Трик за конвертиране на стринг към число
		stringstream ss;
		ss.str(line.substr(lastSpace + 1));
		ss >> iq;

		cout << name << " " << iq << endl;
	}
}

struct Student {
	char name[20];
	int age;
};

void third() {
	// Незадължителна част
	ofstream output("binary.db", ios::binary);

	int n;
	cin >> n;

	Student temp;

	for (int i = 0; i < n; i++) {
		cin >> temp.name >> temp.age;
		output.write((const char*)&temp, sizeof(Student));
	}

	output.close();
	//

	Student newRecruit;
	cout << "newRecruit: ";
	cin >> newRecruit.name >> newRecruit.age;

	int position;
	cin >> position;

	fstream bin("binary.db", ios::binary | ios::in | ios::out);

	// Намираме броя байтове във файла, като преместим указателя на текущата позиция най-отзад
	// и върнем колко байта е отместването с tellg
	bin.seekg(0, ios::end);
	int fileSize = bin.tellg();
	// Броят студенти получаваме, като разделим броя байтове на байтовете за всеки студент
	int students = fileSize / sizeof(Student);

	// Връщаме се обратно в началото
	bin.seekp(0, ios::beg);

	// Ще си направим място, за да запишем новия студент на правилната позиция
	for (int i = students - 1; i >= position; i--) {
		// Местим указателя, така че да прочетем следващия студент (в началото това ще е последния)
		bin.seekp(i * sizeof(Student), ios::beg);
		// Четем студента
		bin.read((char*)&temp, sizeof(Student));
		// Прочели сме го и вече автоматично сме веднага след него и можем да го запишем
		bin.write((const char*)&temp, sizeof(Student));
	}

	// Вече имаме място да си запишем студента, но още не сме го направили
	bin.seekp(position * sizeof(Student), ios::beg);
	bin.write((const char*)&newRecruit, sizeof(Student));

	// Проверка
	bin.seekp(0, ios::beg);

	while (bin.read((char*)&temp, sizeof(Student)))
		cout << temp.name << " " << temp.age << endl;

	bin.close();
}

int main() {
//	first();
//	second();
//	third();
}