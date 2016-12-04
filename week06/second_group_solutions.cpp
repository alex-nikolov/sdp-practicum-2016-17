#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

void transform(string const& input, string const& output) {
    ifstream in(input.c_str());
    ofstream out(output.c_str());
    
    int number;
    list<int> li;
    
    while (in >> number)
        li.push_back(number);

    list<int> transformed;
    list<int>::iterator front = li.begin();
    list<int>::reverse_iterator back = li.rbegin();
    
    for (int i = 0; i < li.size() / 2; i++, front++, back++) {
        transformed.push_back(*front);
        transformed.push_back(*back);
    }
    
    if (li.size() % 2 == 1)
        transformed.push_back(*front);
    
    for (list<int>::iterator it = transformed.begin(); it != transformed.end(); it++)
        out << *it << " ";
}

list<int> convertToList(string const& str) {
    list<int> l;
    
    for (int i = 0; i < str.size(); i++)
        l.push_back(str[i] - '0');
    
    return l;
}

// Връща указател към списъка, съдържащ по-голямото число.
list<int> const* biggerNumber(list<int> const& first, list<int> const& second) {
    if (first.size() > second.size())
        return &first;
    if (first.size() < second.size())
        return &second;

    list<int>::const_iterator f = first.begin();
    list<int>::const_iterator s = second.begin();
    for(; f != first.end(); f++, s++) {
        if (*f > *s)
            return &first;
        if (*f < *s)
            return &second;
    }
    
    return NULL;
}

void subtract(string const& input, string const& output) {
    ifstream in(input.c_str());
    ofstream out(output.c_str());
    
    string firstLine, secondLine;
    getline(in, firstLine);
    getline(in, secondLine);
    
    list<int> first = convertToList(firstLine);
    list<int> second = convertToList(secondLine);
    
    // Връщаме си указател към по-голямото число. Може и чрез swap,
    // но би се губило време за копиране.
    list<int> const* bigger = biggerNumber(first, second);
    
    if (!bigger) {
        out << 0;
        return;
    }

    list<int> const* smaller = (&first == bigger) ? &second : &first;
    
    list<int>::const_reverse_iterator bigIt = bigger->rbegin();
    list<int> result;
    // Едно наум, в началото е false
    bool carryTheOne = false;
    
    for (list<int>::const_reverse_iterator smallIt = smaller->rbegin(); smallIt != smaller->rend(); smallIt++) {
        int sub = *bigIt - *smallIt - carryTheOne;

        // Ако от текущата цифра в по-голямото число извадим текущата в по-малкото и извадим и евентуалното едно наум
        // и получим число, >= 0, тогава го добавяме в резултата и вече нямаме едно наум.
        if (sub >= 0) {
            result.push_front(sub);
            carryTheOne = false;
        }
        
        // В противен случай си взимаме единичка от предната цифра и едно наум става истина.
        else {
            result.push_front(sub + 10);
            carryTheOne = true;
        }
        bigIt++;
    }

    // Сега третираме случая, в който са останали цифри от по-голямото число.
    // Възможно е и просто да си добавим водещи нули в по-малкото число, но в сегашното решение
    // не можем да го използваме, тъй като smaller е указател към константа. Това се налага,
    // тъй като функцията biggerNumber приема const&.
    while (bigIt != bigger->rend()) {
        int sub = *bigIt - carryTheOne;

        if (*bigIt - carryTheOne < 0)
            result.push_front(9);
        else {
            result.push_front(sub);
            carryTheOne = false;
        }
        
        bigIt++;
    }
    
    // Възможноо е да има водещи нули отпред, например при 12345 - 12344
    while (result.front() == 0)
        result.pop_front();
    
    for (list<int>::const_iterator it = result.begin(); it != result.end(); it++)
        out << *it;
}

int main() {
    string input = "one.txt";
    string output = "one_r.txt";

    transform(input, output);

    input = "abc.txt";
    output = "xyz.txt";
    
    subtract(input, output);
}