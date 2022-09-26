#include <iostream>;
#include <string>;
#include <cmath>;
#include<iomanip>;
using namespace std;

bool check_string(string input_string)
{
	bool dot_found = false;
	for (int i = 0; i < input_string.length(); i++)
	{
		char symbol = input_string[i];
		if (i != 0 && symbol == '-')
			return false;
		if (symbol == '.')
		{
			if (dot_found == true)
				return false;
			else dot_found = true;
		}
		if (isdigit(symbol) == 0 && symbol != '.' && symbol != '-')
			return false;
		if (isspace(symbol) != 0)
			return false;
	}
	return true;
}
int factorial(int i)
{
	if (i == 0) return 1;
	else return i * factorial(i - 1);
}

double number_a(int n, double x)
{
	double a = pow(-1, n + 1) * (n - 1) * pow(x, n) / factorial(n);
	return a;
}

double number_SN(int n, double x)
{
	double current_a = number_a(n, x);
	double next_a = number_a(n + 1, x);
	double SN = next_a - current_a;
	return SN;
}

double number_alphaN(int n, double x, double SN)
{
	double next_a = number_a(n + 1, x);
	double alphaN = fabs(next_a / SN);
	return alphaN;
}
void output(int n, double a, double SN, double alphaN)
{
	cout << "n = " << setw(4) << n << " | ";
	cout << "a = " << setw(13) << a << " | ";
	cout << "SN = " << setw(15) << SN << " | ";
	cout << "alphaN = " << setw(15) << alphaN;
	cout << endl;
}

int main()
{
	string answer;
	double a;
	double SN;
	int n = 1;
	double alphaN;
	do
	{
		n = 1;
		string input_x;
		string input_a;
		bool correct_input = false;
		while (correct_input == false)
		{
			cout << "Enter x\n";
			getline(cin, input_x);
			if (check_string(input_x) == false)
			{
				cout << "Enter correct x ( number )\n";
				input_x.clear();
			}
			else correct_input = true;
		}
		correct_input = false;
		while (correct_input == false)
		{
			cout << "Enter a\n";
			getline(cin, input_a);
			if (check_string(input_a) == false)
			{
				cout << "Enter correct a ( number )\n";
				input_a.clear();
			}
			else correct_input = true;

		}
		double x = stod(input_x);
		double alpha = stod(input_a);
		if (alpha != int(alpha))
		{
			do 
			{
				a = number_a(n, x);
				SN = number_SN(n, x);
				alphaN = number_alphaN(n, x, SN);
				output(n, a, SN, alphaN);
				++n;
			} while (alphaN < alpha);
			cout << "Do you want to restart a programm? (y/n)\n";
			cin >> answer;

		}
		if (alpha == int(alpha))
		{
			while (n <= alpha)
			{
				a = number_a(n, x);
				SN = number_SN(n, x);
				alphaN = number_alphaN(n, x, SN);
				output(n, a, SN, alphaN);
				++n;
			}
			cout << "Do you want to restart a programm? (y/n)\n";
			cin >> answer;

		} cin.ignore();
	} while (answer == "y");
}