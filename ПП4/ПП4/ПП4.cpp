
#include <iostream>
#include <fstream> // подключение библиотек
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>


using namespace std;

bool check_int(string input_string) // функция проверки ввода
{
	if (input_string.empty()) // на пустую строку
		return false;
	for (int i = 0; i < input_string.length(); i++)
	{
		char symbol = input_string[i];
		if (i != 0 && symbol == '-')
			return false;
		if (symbol == '.') // на нецелые числа
			return false;
		if (isdigit(symbol) == 0) // на буквы
			return false;
		if (isspace(symbol) != 0) // на пробел
			return false;
	}
	int num = stoi(input_string);
	if (num < 0) // чтобы размер вектора был не меньше 2
		return false;
	return true;
}

bool check_int(string input_string, int sym_am) // функция проверки ввода
{
	if (input_string.empty()) // на пустую строку
		return false;
	for (int i = 0; i < input_string.length(); i++)
	{
		char symbol = input_string[i];
		if (i != 0 && symbol == '-')
			return false;
		if (symbol == '.') // на нецелые числа
			return false;
		if (isdigit(symbol) == 0) // на буквы
			return false;
		if (isspace(symbol) != 0) // на пробел
			return false;
	}
	int num = stoi(input_string);
	if (num < (sym_am + 2)) // чтобы размер вектора был не меньше 2
		return false;
	return true;
}

void changing_letters(vector <vector<char>>& input, int word_s, int sym_am)
{
	int not_alpha;
	cout << endl;
	for (int i = 0; i < input.size(); ++i)
	{
		not_alpha = 0;
		for (int j = 0; j < input[i].size(); ++j)
		{
			if (!isalpha(input[i][j]) && (input[i][j] != '\n' || input [i][j] != ' '))
				++not_alpha;
		}
		if ((input[i].size() - not_alpha) > word_s) // заменяю последние буквы в словах
		{
			for (int j = input[i].size() - sym_am - not_alpha; j < input[i].size() - not_alpha; ++j)
			{
				input[i][j] = 'x';
			}
		}
	}
	ofstream fout("output.txt"); // записываю результаты в файл
	for (int i = 0; i < input.size(); ++i)
	{
		for (int j = 0; j < input[i].size(); ++j)
		{
			fout << input[i][j];
		}
	}
	fout.close();
}


void changing_letters(vector <string>& str_input, int word_s, int sym_am)
{
	int not_alpha;
	cout << endl;
	for (int i = 0; i < str_input.size(); ++i)
	{
		not_alpha = 0;
		for (int j = 0; j < str_input[i].size(); ++j)
		{
			if (!isalpha(str_input[i][j]) && (str_input[i][j] != '\n' || str_input[i][j] != ' '))
				++not_alpha;
		}
		if ((str_input[i].size() - not_alpha) > word_s) // заменяю последние буквы в словах
		{
			for (int j = str_input[i].size() - sym_am - not_alpha; j < str_input[i].size() - not_alpha; ++j)
			{
				str_input[i][j] = 'x';
			}
		}
	}
	ofstream fout("output_string.txt"); // записываю результаты в файл
	for (int i = 0; i < str_input.size(); ++i)
	{
		for (int j = 0; j < str_input[i].size(); ++j)
		{
			fout << str_input[i][j];
		}
	}
	fout.close();
}


int main()
{
	string answer;
	string str;
	string word_size;
	string sym_amount;
	char symbol;
	int i = 0;
	int j = 0;
	int zapuski = 0;
	long double string_summ = 0;
	long double mine_summ = 0;
	do
	{
		++zapuski;
		int word_s;
		bool correct_input = false;
		while (correct_input == false) //цикл ввода
		{
			cout << "Enter amount of changing symbols ( int, one number )\n\n"
				<< "Answer: ";
			getline(cin, sym_amount);
			cout << endl;
			if (check_int(sym_amount) == false)
			{
				cout << "Enter correct amount of changing symbols (int, one number, amount of changing symbols should be >= 0 )\n\n";
			}
			else correct_input = true;
		}
		correct_input = false;
		int sym_am = stoi(sym_amount);
		if (sym_am != 0)
		{
			while (correct_input == false) //цикл ввода
			{
				cout << "Enter word size ( int, one number )\n\n"
					<< "Answer: ";
				getline(cin, word_size);
				cout << endl;
				if (check_int(word_size, sym_am) == false)
				{
					cout << "Enter correct word size (int, one number, word size should be >= " << sym_am + 2 << ")\n\n";
				}
				else correct_input = true;
			}
			word_s = stoi(word_size);
		}
		else
		{
			word_s = 0;
		}
		long double start_time = clock();
		cout << "This is string method : \n\n";;
		vector <string> str_input;
		str_input.push_back("");
		ifstream fin("test1.txt");
		if (!fin.is_open()) // небольшая проверка на наличие файла
			cout << "This file cant be open!\n";
		else
		{
			cout << "Words in this file: \n\n";
			while ((symbol = fin.get()) != EOF)// чтение файла
			{
				if (symbol != ' ') // запись символов в строке
				{
					str_input[i].push_back(symbol);
					if (symbol == '\n') {
						++i;
						str_input.push_back("");
					}
				}
				else
				{
					str_input[i].push_back(' ');
					++i;
					str_input.push_back("");
				}
				cout << symbol;
			}
			fin.close();
			cout << endl;
		}
		changing_letters(str_input, word_s, sym_am);
		ifstream fin2("output_string.txt");
		if (!fin2.is_open()) // небольшая проверка на наличие файла
			cout << "This file cant be open!\n";
		else // чтение слов из другого файла
		{
			cout << "Edited words in another file: \n\n";
			while (getline(fin2, str))
			{
				cout << str << endl;
			}
			fin2.close();
		}
		i = 0;
		j = 0;
		long double string_time = clock() - start_time;
		/// разделение способов
		cout << endl << "---------------------" << endl << "This is my method : \n\n";
		vector <vector<char>> input;
		input.push_back(vector<char>());
		ifstream fin1("test1.txt");
		if (!fin1.is_open()) // небольшая проверка на наличие файла
			cout << "This file cant be open!\n";
		else
		{
			cout << "Words in this file: \n\n";
			while ((symbol = fin1.get()) != EOF)// чтение файла
			{
				if (symbol != ' ') // запись символов в строке
				{
					input[i].push_back(symbol);
					if (symbol == '\n') {
						++i;
						input.push_back(vector <char>());
					}
				}
				else
				{
					input[i].push_back(' ');
					++i;
					input.push_back(vector<char>());
				}
				cout << symbol;
			}
			fin.close();
			cout << endl;
		}
		changing_letters(input, word_s, sym_am);
		ifstream fin3("output.txt");
		if (!fin3.is_open()) // небольшая проверка на наличие файла
			cout << "This file cant be open!\n";
		else // чтение файлов из другого файла
		{
			cout << "Edited words in another file: \n\n";
			while ((symbol = fin3.get()) != EOF)
			{
				cout << symbol;
			}
			fin3.close();
		}
		long double mine_time = clock() - string_time - start_time;
		cout << endl << endl << "String time is: " << string_time / CLOCKS_PER_SEC << endl
			<< "My time is: " << mine_time / CLOCKS_PER_SEC << endl;
		string_summ += string_time / CLOCKS_PER_SEC;
		mine_summ += mine_time / CLOCKS_PER_SEC;
		cout << endl << "Avarange string time is : " << string_summ / zapuski << endl;
		cout << "Avarange mine time is : " << mine_summ / zapuski << endl
			<< endl << "If you wanna restart programm input any symbol except 'n' " << endl;
		getline(cin, answer);
		i = 0;
		j = 0;
		cout << endl << "---------------------" << endl;
	} while (answer != "n");
}