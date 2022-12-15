#include <iostream>
#include <string>

using namespace std;

//вариант 20

bool check_double(const string& input)
{
	bool dot_found = false;
	if (input.empty())
		return false;
	for (int i = 0; i < input.length(); i++)
	{
		char symbol = input[i];
		if (i != 0 && symbol == '-')
			return false;
		if (symbol == '.')
		{
			if (dot_found)
				return false;
			else
				dot_found = true;
		}
		if (!isdigit(symbol) && symbol != '-' && symbol != '.' && isspace(symbol))
			return false;
	}
	if ((stold(input) > 1.7E+308) || (stod(input) < 0))
		return false;
	return true;
}

bool check_int(const string& input)
{
	bool dot_found = false;
	if (input.empty())
		return false;
	for (int i = 0; i < input.length(); i++)
	{
		char symbol = input[i];
		if ((i != 0 && symbol == '-') || (symbol == '.'))
			return false;
		if (!isdigit(symbol) && symbol != '-' && isspace(symbol))
			return false;
	}
	if ((stoll(input) > 2147483647) || (stoll(input) < 0))
		return false;
	return true;
}

double percentage(double& deposit, const double& rate, int& months)
{
	return deposit * pow(1 + rate, months);
}

void user_input(const char& flag, string& input)
{
	bool correct_input = false;
	while (!correct_input)
	{
		if (!flag)
			cout << "Input an initial deposit > ";
		if (flag)
			cout << "Input a monthly deposit rate >  ";
		getline(cin, input);
		if (!check_double(input))
		{
			cout << "Wrong input!\n";
			correct_input = false;
		}
		else
			correct_input = true;
	}
}

void months_input(string& input)
{
	bool correct_input = false;
	while (!correct_input)
	{
		cout << "Input the number of months > ";
		getline(cin, input);
		if (!check_int(input))
		{
			cout << "Wrong input!\n";
			correct_input = false;
		}
		else
			correct_input = true;
	}
}

int main()
{
	string answ = "y";
	string input;
	bool flag;
	cout << "Deposit percentage\n";
	while (answ != "n")
	{
		flag = false;
		user_input(flag, input);
		double deposit = stod(input);
		flag = true;
		user_input(flag, input);
		double rate = stod(input);
		months_input(input);
		int months = stoi(input);
		cout << "Result: " << percentage(deposit, rate, months) << endl << "Continue? (any symbol/n)> ";
		getline(cin, answ);
	}
}
