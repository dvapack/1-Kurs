#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool check_input(const string& input, const char& flag)
{
	if (input.empty())
		return false;
	for (int i = 0; i < input.length(); i++)
	{
		char symbol = input[i];
		if (!flag && ((symbol == '-') || symbol == ('0')))
			return false;
		if ((symbol == '.') || (i && !isdigit(symbol) && (symbol != '-')) || isspace(symbol))
			return false;
	}
	if ((stoll(input) > 2147483647) || (stoll(input) < -2147483648))
		return false;
	return true;
}

void very_fast_sorting(vector <int>& numbers)
{
	int j;
	for (int i = 0; i < numbers.size(); ++i) // сама сортировка
	{
		for(int j = 0; j < numbers.size())
	}
	
}

int number(const vector<int>& numbers)
{
	for (int i = numbers.size() - 1; i >= 0; --i)
	{
		/*if (i && (numbers[i] - numbers[i - 1] > 1))
			return numbers[i - 1] + 1;*/
		if (i && (numbers[i] >= 0) && (numbers[i - 1] >= 0) && (numbers[i] - numbers[i - 1] > 1))
			return numbers[i - 1] + 1;
	}
	return numbers[numbers.size() - 1] + 1;
}

int main()
{
	string answ;
	string input;
	bool correct_input;
	char flag;
	do
	{
		correct_input = false;
		flag = 0;
		cout << "Another number\n";
		while (!correct_input)
		{
			cout << "Input the number of integers > ";
			getline(cin, input);
			if (!check_input(input, flag))
			{
				cout << "Wrong input! Please enter a positive integer\n";
				correct_input = false;
			}
			else
				correct_input = true;
		}
		correct_input = false;
		int size = stoi(input);
		vector <int> numbers(size);
		flag = 1;
		for (int i = 0; i < size; ++i)
		{
			while (!correct_input)
			{
				cout << "Input the integer # " << i + 1 << " > ";
				getline(cin, input);
				if (!check_input(input, flag))
				{
					cout << "Wrong input! Please enter an integer\n";
					correct_input = false;
				}
				else
					correct_input = true;
			}
			numbers[i] = stoi(input);
			correct_input = false;
		}
		very_fast_sorting(numbers);
		cout << "Result: " << number(numbers) << endl << "Continue? (any symbol/n)> ";
		getline(cin, answ);
	} while (answ != "n");
}
