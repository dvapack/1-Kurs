#include <iostream>
#include <string>

using namespace std;

bool check_input(const string& input)
{
	if (input.empty())
		return false;
	for (int i = 0; i < input.length(); i++)
	{
		char symbol = input[i];
		if ((symbol == '-') || (symbol == '.') || !isdigit(symbol) || isspace(symbol))
			return false;
	}
	if (stoll(input) > 2147483647)
		return false;
	return true;
}

string number(int& num)
{
	string result;
	while (num)
	{
		result.insert(0, to_string(num % 2));
		num /= 2;
	}
	return result;
}

int main()
{
	string answ;
	string input;
	bool correct_input;
	do
	{
		correct_input = false;
		cout << "Translating a number from decimal to binary\n";
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
		int num = stoi(input);
		cout << "Result: " << number(num) << endl << "Continue? (any symbol/n)> ";
		getline(cin, answ);
	} while (answ != "n");
}
