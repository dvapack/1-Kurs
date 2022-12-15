#include <iostream>
#include <string>
#include <vector>

using namespace std;

//вариант 14

bool check_input(const string& input, const char& flag)
{
	if (input.empty())
		return false;
	for (int i = 0; i < input.length(); i++)
	{
		char symbol = input[i];
		if (!flag && ((symbol == '-')))
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
	for (int i = 0; i < numbers.size(); ++i)
	{
		if (numbers.size() > 1)
		{
			for (int j = i + 1; j < numbers.size(); ++j)
				if (numbers[i] > numbers[j])
					swap(numbers[i], numbers[j]);
		}
	}	
}

int number(const vector<int>& numbers)
{

	for (int i = numbers.size() - 1; i >= 0; --i)
	{
		/*if (i && (numbers[i] >= 0) && (numbers[i - 1] >= 0) && (numbers[i] - numbers[i - 1] > 1))
			return numbers[i - 1] + 1;
		if(!i)
			return numbers[numbers.size() - 1] + 1;*/
		if (i && abs(numbers[i] - numbers[i - 1]) > 1)
			return numbers[i - 1] + 1;
		if (!i && numbers[numbers.size() - 1] + 1 != numbers[0])
			return numbers[numbers.size() - 1] + 1;
		if (!i)
			for (int i = 0; i < numbers.size() - 1; ++i)
			{
				if ((i != numbers.size()-1) && abs(numbers[i+1] - numbers[i]) > 1)
					return numbers[i] + 1;
			}
	}
}

void size_input(string& input)
{
	char flag = 0;
	bool correct_input = false;
	while (!correct_input)
	{
		cout << "Input the number of integers > ";
		getline(cin, input);
		if (!check_input(input, flag) || !stoi(input))
		{
			cout << "Wrong input! Please enter a positive integer\n";
			correct_input = false;
		}
		else
			correct_input = true;
	}
}

void elements_input(vector<int>& numbers, string& input)
{
	char flag = 1;
	bool correct_input = false;
	for (int i = 0; i < numbers.size(); ++i)
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
}

int main()
{
	string answ = "y";
	string input;
	cout << "Another number\n";
	while (answ != "n")
	{
		size_input(input);
		int size = stoi(input);
		vector <int> numbers(size);
		elements_input(numbers, input);
		very_fast_sorting(numbers);
		cout << "Result: " << number(numbers) << endl << "Continue? (any symbol/n)> ";
		getline(cin, answ);
	}
}
