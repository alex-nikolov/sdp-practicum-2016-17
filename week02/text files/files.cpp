#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

// В задача 4, вариант 2 проверяваме дали намереното срещане на word
// е наистина отделна дума, а не поддума на друга дума
// Може да стане и със заместване с регулярен израз в C++ 11
bool isWholeWord(string content, string word, size_t index) {
	bool precededByWhitespace = (index == 0 || isspace(content[index - 1]));
	bool followedByWhitespace = (index == content.size() - word.size() ||
							     isspace(content[index + word.size()]));
	return precededByWhitespace && followedByWhitespace;
}

// Задача 1
void first() {
	string line;
	getline(cin, line); //Четем цял ред
	ofstream output("first.txt");
	output << line;
	output.close(); // Затваряме файла, защото сега ще отворим нов файл за писане
					// и поддържането на 2 отделни обекта за четене и писане е несъвместимо
        			// Друг вариант е да си направите fstream обект, който поддържа четене и писане
	ifstream input("first.txt");
	getline(input, line);
	input.close();
	cout << line;
}

// Задача 2
void second() {
	int x, y;
	int minX, maxX, minY, maxY;
	ifstream input("second.txt");

	input >> x >> y;
	minX = maxX = x;
	minY = maxY = y;
  
    // Докато можем да четем от input и да записваме в x и y
	while (input >> x >> y) { 
		minX = x < minX ? x : minX;
		maxX = x > maxX ? x : maxX;
		
		minY = y < minY ? y : minY;
		maxY = y > maxY ? y : maxY;
	}
	cout << (maxX - minX) * (maxY - minY);
	input.close();
	
	/* Втори вариант със stringstream, за любознателните
	stringstream ss;
	string line2;
	while (getline(input, line)) {
		ss.str(line);
		ss >> x >> y;
		//сметки
	}
	*/
}

// Задача 3
void third() {
	char symbol;
	cin >> symbol;
	ifstream input("third.txt");
	string line;
	int lineNumber = 1;
	
	while(getline(input, line)) {
		for (int i = 0; i < line.size(); i++) {
			if (line[i] == symbol)
				cout << "Line: " << lineNumber << ", position: " << i + 1 << endl;
		}
		lineNumber++;
	}
	input.close();
}

// Задача 4, вариант 1
// Пазите си съдържанието на целия файл в стринг, заменяте всяко срещане на думата
// и го записвате във файла, изтривайки предишното съдържание.
// Този подход ще работи и в случая, когато заместваната дума е с различна дължина от заместващата.
void fourth_var_one() {
	ifstream input("fourth.txt");
	string naughtyWord;
	cin >> naughtyWord;
	string censored(naughtyWord.size(), '*');
	string content;

	// Взимаме цялото съдържание на файла наведнъж.
	getline(input, content, (char) input.eof());
	size_t index = 0;
	while (content.size() > 0) {
		index = content.find(naughtyWord, index);

		if (index == string::npos)
			break;
		// Не разглеждаме случая, в който търсената дума не е "цяла" дума,
		// т.е. е поддума на друга дума.
		if (isWholeWord(content, naughtyWord, index))
			content.replace(index, naughtyWord.size(), censored);

		index += naughtyWord.size();
	}
	input.close();
	
	// ios::out винаги е set-нат, така че можем да го пропуснем
	ofstream output("fourth.txt", ios::trunc);
	output << content;
	output.close();
}

// Задача 4, вариант 2
// Тук съществено използваме условието, че думата, с която искаме да заместим,
// има същата дължина като заместената.
// Забележка: Нестабилно е на gcc.
void fourth_var_two() {
	fstream file("fourth.txt");
	string naughtyWord;
	cin >> naughtyWord;
	string censored(naughtyWord.size(), '*'); //Създава стринг с дължина naughtyWord.size(), състоящ се от звездички
	string word;
	cout << naughtyWord << " " << censored << endl;

	while (file >> word) {
		if (word == naughtyWord) {
			// Мести указателя в текущия файл за писане толкова символа назад,
			// колкото е дължината на намерената дума
			file.seekp(-(int)naughtyWord.size(), ios::cur);
			// Когато думата е последна във файл, без да е следвана от интервал или нов ред,
			// програмата няма да работи без да се изчисти статуса за край на файл
			if (file.eof()) {
				file.clear();
			}
			file << censored;
			// Изчиства буфера и по-този начин насилствено кара съдържанието му да се
			// запише във файла. В случая не работи без него :)
			file.flush();			
		}
	}
	file.close();
}

// Задача 5
void fifth() {
	string digits;
	ifstream input("fifth.txt");
	char temp;

	while(input >> temp) {
		if (temp >= '0' && temp <= '9')
			digits += temp;
	}

	// Един начин за превръщане на стринга в число
	stringstream ss;
	ss.str(digits);
	int number;
	ss >> number;
	cout << number;
	input.close();
	
	//Вариант 2 - заделяте си вектор (масив), слагате всяка цифра във вектора и правите сметки като по УП :)
}

// Задача 6
void sixth() {
	ifstream input("sixth.txt");
	string name;
	int number;

	input >> name >> number;
	string maxName = name;
	int maxNumber = number;
	
	while(input >> name >> number) {
		if (number > maxNumber) {
			maxNumber = number;
			maxName = name;
		}
	}
	
	cout << maxName;
	input.close();
}

int main() {
	//first();
	//second();
	//third();
	//fourth_var_one();
	//fourth_var_two();
	//fifth();
	//sixth();
}