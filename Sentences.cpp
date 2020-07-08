#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include "Set.h"

bool readSent(const char* filename, vector <Set>& sentences);
bool readSent(const char* filename, vector<vector<string>>& sent_numb);

int main()
{
	setlocale(LC_ALL, "Russian");
	vector <Set> sentences;
	vector <vector<string>> sent_numb;
	readSent("Text.txt", sentences); //формируем набор множеств
	readSent("Text.txt", sent_numb); //формируем набор предложений
	ofstream out("Results.txt");
	int i = 0;
	for (vector<Set>::iterator it = sentences.begin(); it != sentences.end(); it++) {
		int j = i;
		for (vector<Set>::iterator it2 = it; it2 != sentences.end(); it2++) { //сравниваем каждое множество с остальными, идущими после него
			if ((*it) == (*it2) && it != it2) {									//если множества равны, выводим множества и предложени€
				out << "ќдинаковые множества " <<endl<<"ћножество 1: "<< *it << endl << "ћножество 2: " << *it2 << endl<<"ѕредложение 1: ";
				for (vector<string>::iterator it3 = sent_numb.at(i).begin(); it3 != sent_numb.at(i).end(); it3++)
					out << *it3;
				out << endl<< "ѕредложение 2: ";
				for (vector<string>::iterator it3 = sent_numb.at(j).begin(); it3 != sent_numb.at(j).end(); it3++)
					out << *it3;
				out << endl << endl;
			}
			if ((*it) - (*it2) == (*it)) {		//если множества не содержат одинаковых символов, выводим множества и предложени€
				out << "–азные множества " << endl << "ћножество 1: "<< *it << endl << "ћножество 2: "<< *it2 << endl<< "ѕредложение 1: ";
				for (vector<string>::iterator it3 = sent_numb.at(i).begin(); it3 != sent_numb.at(i).end(); it3++)
					out << *it3;
				out << endl << "ѕредложение 2: ";
				for (vector<string>::iterator it3 = sent_numb.at(j).begin(); it3 != sent_numb.at(j).end(); it3++)
					out << *it3;
				out << endl << endl;
			}
			j++;
		}
		i++;

	}
	return 0;
}

bool readSent(const char* filename, vector <Set>& sentences) {
	ifstream in(filename);
	if (!in.is_open())
	{
		cout << "Can't open the file.";
		return false;
	}
	while (!in.eof()) {
		set <unsigned char> sent;
		unsigned char c=' ';
		unsigned char cc;
		while (c!='.' && c != '!' && c != '?'){
			in >> cc;
			if (int(cc) >= 192 && int(cc) <= 255) { //если считанный символ - символ русского алфавита
				if (int(cc) < 224)
					cc += unsigned char(32); // приводим все заглавные символы к строчным 
				sent.insert(cc);			//заполн€ем множество символов
			}
			c = cc;
		}
		if (!sent.empty())					//заполн€ем множество из множеств символов
			sentences.push_back(sent);
	}
	in.close();
	return true;
}

bool readSent(const char* filename, vector<vector<string>>& sent_numb) {
	ifstream in(filename);
	string s;
	if (!in.is_open())
	{
		cout << "Can't open the file.";
		return false;
	}
	while (!in.eof()) {
		vector <string> sent;
		do {
			in >> s;				//считываем строку
			sent.push_back(s);		//вставл€ем строку в множество строк
			sent.push_back(" ");   //добавл€ем пробел между словами
		} while (s.find('.') > 100 && s.find('?') > 100 && s.find('!') > 100);		//пока не встретим . ! или ?
		sent_numb.push_back(sent);		//записываем предложение в вектор предложений
	}
	in.close();
	return true;
}