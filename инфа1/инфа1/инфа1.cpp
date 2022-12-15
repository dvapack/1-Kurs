#include <iostream>
#include <string>
#include <cmath>
#include <bitset>

using namespace std;

//вариант 1

bool check_input(const string& input)
{
	if (input.empty())
		return false;
	for (int i = 0; i < input.length(); i++)
	{
		char symbol = input[i];
		if ((symbol == '.') || ((i) && (symbol == '-')) || ((symbol != '-') && !isdigit(symbol)) || isspace(symbol))
			return false;
	}
	if (stoll(input) > 2147483647 || stoll(input) < -2147483648)
		return false;
	return true;
}

string decel_to_bin(int& num)
{
	string result = "00000000000000000000000000000000";
	int i = 1;
	if (num < 0)
	{
		num = ~num;
		do
		{
			result.replace(32 - i, 1, to_string(num % 2));
			num /= 2;
			++i;
		} while (num && i != 33);
		for (int i = 0; i < 32; ++i)
		{
			result[i] == '1' ? result[i] = '0' : result[i] = '1';
		}
		return result;
	}
	if (num >= 0)
	{
		do
		{
			result.replace(32-i, 1, to_string(num % 2));
			num /= 2;
			++i;
		} while (num && i != 33);
		return result;
	}
}

void int_input(string& input, int& num)
{
	bool correct_input = false;
	while (!correct_input)
	{
		cout << "Input an integer > ";
		getline(cin, input);
		if (!check_input(input))
		{
			cout << "Wrong input! Please enter an integer\n";
			correct_input = false;
		}
		else
			correct_input = true;
	}
	num = stoi(input);
}


int main()
{
	string answ = "y";
	string input;
	int num = 0;
	cout << "Translating a number from decimal to binary\n";
	while (answ != "n")
	{
		int_input(input, num);
		cout << bitset<32>(num) << " - bitset result" << endl;
		cout << decel_to_bin(num) << " - my result" << endl << "Continue? (any symbol/n)> ";
		getline(cin, answ);
	}
}
