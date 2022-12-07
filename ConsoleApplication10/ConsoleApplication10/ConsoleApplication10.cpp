#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

class SavedNumbers
{
private:
	double n, an, SN, alphaN;
public:
	SavedNumbers()
	{
		n = an = SN = alphaN = 0;
	}
	SavedNumbers(const double& i, const double& aN, const double& SumN, const double& alphN)
	{
		n = i;
		an = aN;
		SN = SumN;
		alphaN = alphN;
	}
	double get_n()
	{
		return n;
	}
	double get_an()
	{
		return an;
	}
	double get_SN()
	{
		return SN;
	}
	double get_alphaN()
	{
		return alphaN;
	}
};

class SavedX
{
private:
	double x;
	vector <SavedNumbers> x_numbers;
public:
	SavedX(const double& X)
	{
		x = X;
	}
	double get_x()
	{
		return x;
	}
	void set_x_numbers(const SavedNumbers& numbers)
	{
		x_numbers.push_back(numbers);
	}
	SavedNumbers get_x_numbers()
	{
		for (int i = 0; i < x_numbers.size(); ++i)
			return x_numbers[i];
	}
	double get_x_numbers_alpha()
	{
		return x_numbers[x_numbers.size() - 1].get_n();
	}
	double get_x_numbers_SN(int i)
	{
		return x_numbers[i].get_SN();
	}
	double get_x_numbers_alphaN(int i)
	{
		return x_numbers[i].get_alphaN();
	}
	double get_x_numbers_an(int i)
	{
		return x_numbers[i].get_an();
	}
};


bool check_string(const string& check, const int& flag)
{
	if (check.empty()) // для отслеживания пустой строки
		return false;
	bool dot_found = false;
	for (int i = 0; i < check.length(); i++)
	{
		char symbol = check[i];
		if (i != 0 && symbol == '-') // минус должен быть только в начале числа
			return false;
		if (symbol == '.')
		{
			if (dot_found == true)
				return false;
			else dot_found = true;
		}
		if (!isdigit(symbol) && symbol != '.' && symbol != '-') // для отслеживания букв
			return false;
		if (flag && symbol == '-')
			return false;
		if (isspace(symbol) != 0) // для отслеживания пробелов в строке
			return false;
	}
	return true;
}

long factorial(const int& n)
{
	if (n == 0) return 1;
	else return n * factorial(n - 1);
}

double a_n(const int& n, const double& x)
{
	return (pow(-1, n + 1) * (n - 1) * pow(x, n)) / factorial(n);
}

double alphaN(const int& n, const double& x, const double& SN)
{
	return fabs(a_n(n + 1, x) / (SN));
}

void print(const double& i, const double& an, const double& SN, const double& alphaN) // функция для вывода всех значений в таблицу
{
	cout << "n = " << setw(4) << i << " | ";
	cout << "a = " << setw(13) << an << " | ";
	cout << "SN = " << setw(15) << SN << " | ";
	cout << "alphaN = " << setw(15) << alphaN;
	cout << endl;
}

void print_again(double& alpha, int& j, vector<SavedX>& saved_X, double& x)
{
	for (int i = 2; i <= saved_X[j].get_x_numbers_alpha(); ++i)
	{
		cout << "f ";
		print(i, saved_X[j].get_x_numbers_an(i - 2), saved_X[j].get_x_numbers_SN(i - 2), saved_X[j].get_x_numbers_alphaN(i - 2));
	}
	double prev_SN = saved_X[j].get_x_numbers_SN(saved_X[j].get_x_numbers_alpha() - 2);
	double SN = 0;
	double an = 0;
	double alpha_N = 0;
	for (int i = saved_X[j].get_x_numbers_alpha() + 1; i <= alpha + 2; ++i)
	{
		an = a_n(i, x);
		SN = prev_SN + an;
		prev_SN = SN;
		alpha_N = alphaN(i, x, SN);
		print(i, an, SN, alpha_N);
		SavedNumbers numbers(i, an, SN, alpha_N);
		saved_X[j].set_x_numbers(numbers);
	}
}

void if_P_print_again(double& alpha, int& j, int& i, vector<SavedX>& saved_X, double& x)
{
	double prev_SN = saved_X[j].get_x_numbers_SN(saved_X[j].get_x_numbers_alpha() - 2);
	double SN = 0;
	double an = 0;
	double alpha_N = saved_X[j].get_x_numbers_alphaN(i - 2);
	++i;
	while (alpha < alpha_N)
	{
		an = a_n(i, x);
		SN = prev_SN + an;
		prev_SN = SN;
		alpha_N = alphaN(i, x, SN);
		print(i, an, SN, alpha_N);
		SavedNumbers numbers(i, an, SN, alpha_N);
		saved_X[j].set_x_numbers(numbers);
		++i;
	}
}

void if_alpha_N(const double& alpha, const double& x, vector<SavedX>& saved_X)
{
	double prev_SN = 1;
	double SN = 0;
	double an = 0;
	double alpha_N = 0;
	SavedX s_x(x);
	for (int i = 2; i <= alpha + 2; ++i)
	{
		an = a_n(i, x);
		SN = prev_SN + an;
		prev_SN = SN;
		alpha_N = alphaN(i, x, SN);
		print(i, an, SN, alpha_N);
		SavedNumbers numbers(i, an, SN, alpha_N);
		s_x.set_x_numbers(numbers);
	}
	saved_X.push_back(s_x);
}

void if_alpha_P(const double& alpha, const double& x, vector<SavedX>& saved_X)
{
	double prev_SN = 1;
	double SN = 0;
	double an = 0;
	double alpha_N = 0;
	SavedX s_x(x);
	int i = 2;
	do
	{
		an = a_n(i, x);
		SN = prev_SN + an;
		prev_SN = SN;
		alpha_N = alphaN(i, x, SN);
		print(i, an, SN, alpha_N);
		SavedNumbers numbers(i, an, SN, alpha_N);
		s_x.set_x_numbers(numbers);
		++i;
	} while (alpha < alpha_N);
	saved_X.push_back(s_x);
}

int main()
{
	int flag; // флаг для проверки ввода
	string input_x, input_a, answ;
	int zapuski;
	vector <SavedX> saved_x;
	do
	{
		zapuski = 0;
		bool correct_input = false;
		while (!correct_input) // ввод Х
		{
			flag = 0; // флаг для проверки ввода
			cout << "Enter x\n";
			getline(cin, input_x);
			if (!check_string(input_x, flag))
			{
				cout << "Enter correct x ( number )\n";
			}
			else correct_input = true;
		}
		correct_input = false;
		while (!correct_input) // ввод погрешности / n, в зависимости от полученных значений
		{
			flag = 1; // флаг для проверки ввода
			cout << "Enter a\n";
			getline(cin, input_a);
			if (!check_string(input_a, flag))
			{
				cout << "Enter correct a ( number )\n";
			}
			else correct_input = true;
		}
		double x = stod(input_x);
		double alpha = stod(input_a);
		for (int i = 0; i < saved_x.size(); ++i)
		{
			if (x == saved_x[i].get_x())
			{
				int j = i;
				if ((alpha == (int)alpha) && (alpha <= saved_x[i].get_x_numbers_alpha() - 2))
				{
					for (int i = 2; i <= alpha + 2; ++i)
					{
						cout << "f ";
						print(i, saved_x[j].get_x_numbers_an(i - 2), saved_x[j].get_x_numbers_SN(i - 2), saved_x[j].get_x_numbers_alphaN(i - 2));
					}
				}
				if ((alpha == (int)alpha) && (alpha > saved_x[i].get_x_numbers_alpha() - 2))
				{
					print_again(alpha, j, saved_x, x);
				}
				if (alpha != (int)alpha)
				{
					int i = 2;
					while ((i < saved_x[j].get_x_numbers_alpha()) && (alpha <= saved_x[j].get_x_numbers_alphaN(i-2)))
					{
						cout << "f ";
						print(i, saved_x[j].get_x_numbers_an(i - 2), saved_x[j].get_x_numbers_SN(i - 2), saved_x[j].get_x_numbers_alphaN(i - 2));
						++i;
					}
					cout << "f ";
					print(i, saved_x[j].get_x_numbers_an(i - 2), saved_x[j].get_x_numbers_SN(i - 2), saved_x[j].get_x_numbers_alphaN(i - 2));
					if_P_print_again(alpha, j, i, saved_x, x);
				}
				zapuski = 1;
			}
		}
		if (!zapuski)
			alpha == (int)alpha ? if_alpha_N(alpha, x, saved_x) : if_alpha_P(alpha, x, saved_x);
		getline(cin, answ);
	} while (answ != "n");
}
