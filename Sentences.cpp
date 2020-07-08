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
	readSent("Text.txt", sentences); //��������� ����� ��������
	readSent("Text.txt", sent_numb); //��������� ����� �����������
	ofstream out("Results.txt");
	int i = 0;
	for (vector<Set>::iterator it = sentences.begin(); it != sentences.end(); it++) {
		int j = i;
		for (vector<Set>::iterator it2 = it; it2 != sentences.end(); it2++) { //���������� ������ ��������� � ����������, ������� ����� ����
			if ((*it) == (*it2) && it != it2) {									//���� ��������� �����, ������� ��������� � �����������
				out << "���������� ��������� " <<endl<<"��������� 1: "<< *it << endl << "��������� 2: " << *it2 << endl<<"����������� 1: ";
				for (vector<string>::iterator it3 = sent_numb.at(i).begin(); it3 != sent_numb.at(i).end(); it3++)
					out << *it3;
				out << endl<< "����������� 2: ";
				for (vector<string>::iterator it3 = sent_numb.at(j).begin(); it3 != sent_numb.at(j).end(); it3++)
					out << *it3;
				out << endl << endl;
			}
			if ((*it) - (*it2) == (*it)) {		//���� ��������� �� �������� ���������� ��������, ������� ��������� � �����������
				out << "������ ��������� " << endl << "��������� 1: "<< *it << endl << "��������� 2: "<< *it2 << endl<< "����������� 1: ";
				for (vector<string>::iterator it3 = sent_numb.at(i).begin(); it3 != sent_numb.at(i).end(); it3++)
					out << *it3;
				out << endl << "����������� 2: ";
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
			if (int(cc) >= 192 && int(cc) <= 255) { //���� ��������� ������ - ������ �������� ��������
				if (int(cc) < 224)
					cc += unsigned char(32); // �������� ��� ��������� ������� � �������� 
				sent.insert(cc);			//��������� ��������� ��������
			}
			c = cc;
		}
		if (!sent.empty())					//��������� ��������� �� �������� ��������
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
			in >> s;				//��������� ������
			sent.push_back(s);		//��������� ������ � ��������� �����
			sent.push_back(" ");   //��������� ������ ����� �������
		} while (s.find('.') > 100 && s.find('?') > 100 && s.find('!') > 100);		//���� �� �������� . ! ��� ?
		sent_numb.push_back(sent);		//���������� ����������� � ������ �����������
	}
	in.close();
	return true;
}