#include <iostream>
#include <string>

using namespace std;

bool check_input(const string& input, const char& flag)
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
			(!flag && dot_found == true) ? false : dot_found = true;
			if (flag) 
				return false;
		}
		if (!isdigit(symbol) && symbol != '-' && symbol != '.' && isspace(symbol))
			return false;
	}
	if ((flag && (stoll(input) > 2147483647) || (stoll(input) < 0)) || (!flag && (stold(input) > 1.7E+308) || (stod(input) < 0)))
		return false;
	return true;
}

double percentage(double& deposit, const double& rate, int& months)
{
	/*while (months)
	{
		deposit += deposit * rate;
		--months;
	}*/
	deposit += deposit * rate;
	return deposit;
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
		cout << "Deposit percentage\n";
		while (!correct_input)
		{
			cout << "Input an initial deposit > ";
			getline(cin, input);
			if (!check_input(input, flag))
			{
				cout << "Wrong input!\n";
				correct_input = false;
			}
			else
				correct_input = true;
		}
		correct_input = false;
		double deposit = stod(input);
		while (!correct_input)
		{
			cout << "Input a monthly deposit rate >  ";
			getline(cin, input);
			if (!check_input(input, flag))
			{
				cout << "Wrong input!\n";
				correct_input = false;
			}
			else
				correct_input = true;
		}
		correct_input = false;
		double rate = stod(input);
		flag = 1;
		while (!correct_input)
		{
			cout << "Input the number of months > ";
			getline(cin, input);
			if (!check_input(input, flag))
			{
				cout << "Wrong input! Please enter an integer\n";
				correct_input = false;
			}
			else
				correct_input = true;
		}
		int months = stoi(input);
		cout << "Result: " << percentage(deposit, rate, months) << endl << "Continue? (any symbol/n)> ";
		getline(cin, answ);
	} while (answ != "n");
}
