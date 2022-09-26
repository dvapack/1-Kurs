#include <iostream>;
#include <string>;
#include <cmath>;
using namespace std;


bool check_string(string input_string)
{
	bool dot_found = false;
	bool number_int;
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



int main()
{
	bool dot_found = false;
	string input_x;
	string input_a;
	string answer;
	do {
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
		double a;
		double S;
		double SN;
		double a_next;
		int n = 1;
		double alphaN;
		int b = -1;
		int N = n + 1;
		int i;
		if (alpha != int(alpha))
		{
			do
			{
				a = pow(b, N) * (n - 1) * pow(x, n) / factorial(n);
				a_next = a + pow(b, N + 1) * (n)*pow(x, n + 1) / factorial(n + 1);
				SN = a_next - a;
				alphaN = fabs(a_next / SN);
				cout << n << "   " << a << "   " << SN << "   " << alphaN << endl;
				++n;
			} while (alphaN < alpha);
			cout << "Do you want to restart a programm? (y/n)\n";
			cin >> answer;
		}
		if (alpha == int(alpha))
		{
			while (n <= alpha)
			{
				a = pow(b, N) * (n - 1) * pow(x, n) / factorial(n);
				a_next = a + pow(b, N + 1) * (n)*pow(x, n + 1) / factorial(n + 1);
				SN = a_next - a;
				alphaN = fabs(a_next / SN);
				cout << n << "   " << a << "   " << SN << "   " << alphaN << endl;
				++n;
			}
			cout << "Do you want to restart a programm? (y/n)\n";
			cin >> answer;
		}

	} while (answer == "y");
}
