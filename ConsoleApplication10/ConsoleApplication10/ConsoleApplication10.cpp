#include <iostream>
#include <string>
#include <cmath>   // подключаем библиотеки
#include <iomanip>
#include <vector>

using namespace std;

bool check_string(string input_string) // функция для проверки ввода
{
	if (input_string.empty()) // для отслеживания пустой строки
		return false;
	bool dot_found = false;
	for (int i = 0; i < input_string.length(); i++)
	{
		char symbol = input_string[i];
		if (i != 0 && symbol == '-') // минус должен быть только в начале числа
			return false;
		if (symbol == '.')
		{
			if (dot_found == true)
				return false;
			else dot_found = true;
		}
		if (isdigit(symbol) == 0 && symbol != '.' && symbol != '-') // для отслеживания букв
			return false;
		if (isspace(symbol) != 0) // для отслеживания пробелов в строке
			return false;
	}
	return true;
}

int factorial(int i) // функция для расчёта факториала числа
{
	if (i == 0) return 1;
	else return i * factorial(i - 1);
}

double number_a(int n, double x) // функция для расчёта n-ого члена ряда
{
	double a = pow(-1, n + 1) * (n - 1) * pow(x, n) / factorial(n);
	return a;
}

double number_SN(double prev_SN, int n, double x) // функция для расчёта частичной суммы
{
	double current_a = number_a(n, x);
	double SN = current_a + prev_SN;
	return SN;
}

double number_alphaN(int n, double x, double SN) // функция для расчёта погрешности
{
	double next_a = number_a(n + 1, x);
	double alphaN = fabs(next_a / (SN + 1));
	return alphaN;
}

void output(int n, double a, double SN, double alphaN) // функция для вывода всех значений в таблицу
{
	cout << "n = " << setw(4) << n << " | ";
	cout << "a = " << setw(13) << a << " | ";
	cout << "SN = " << setw(15) << SN + 1 << " | ";
	cout << "alphaN = " << setw(15) << alphaN;
	cout << endl;
}

void output_again(int n, int j, vector<double> saved_numbers)
{
	cout << "n = " << setw(4) << n << " | ";
	cout << "a = " << setw(13) << saved_numbers[j] << " | ";
	++j;
	cout << "SN = " << setw(15) << saved_numbers[j] + 1 << " | ";
	++j;
	cout << "alphaN = " << setw(15) << saved_numbers[j];
	cout << endl;
}

void repeat_output(int y, double prev_alpha, double alpha, vector <vector<double>> saved_numbers)
{
	int j;
	int n;
	cout << "You've already inserted this 'x', so the programm will output saved numbers" << endl;
	if (alpha != int(alpha) && alpha < y)
	{
		if (prev_alpha == alpha)
		{
			for (int i = 0; i < saved_numbers.size(); ++i)
			{
				n = i + 1;
				j = 0;
				output_again(n, j, saved_numbers[i]);
			}
		}
		if (prev_alpha > alpha)
		{
			int ch = 0;
			for (int i = 0; i < saved_numbers.size(); ++i)
			{
				if (alpha <= saved_numbers[i][2] && ch != 1)
				{
					n = i + 1;
					j = 0;
					output_again(n, j, saved_numbers[i]);
				}
				if (alpha > saved_numbers[i][2] && ch != 1)
				{
					n = i + 1;
					j = 0;
					output_again(n, j, saved_numbers[i]);
					ch = 1;
				}
			}
		}
		if (prev_alpha < alpha)
		{
			int ch = 0;
			for (int i = 0; i < saved_numbers.size(); ++i)
			{
				if (alpha <= saved_numbers[i][2] && ch != 1)
				{
					n = i + 1;
					j = 0;
					output_again(n, j, saved_numbers[i]);
				}
				if (alpha > saved_numbers[i][2] && ch != 1)
				{
					n = i + 1;
					j = 0;
					output_again(n, j, saved_numbers[i]);
					ch = 1;
				}
			}
		}

	}
	if (alpha != int(alpha) && alpha > y)
	{
		if (prev_alpha == alpha)
		{
			for (int i = 0; i < saved_numbers.size(); ++i)
			{
				n = i + 1;
				j = 0;
				output_again(n, j, saved_numbers[i]);
			}
		}
		if (prev_alpha > alpha)
		{
			int ch = 0;
			for (int i = 0; i < saved_numbers.size(); ++i)
			{
				if (alpha > saved_numbers[i][2] && ch != 1)
				{
					n = i + 1;
					j = 0;
					output_again(n, j, saved_numbers[i]);
				}
				if (alpha <= saved_numbers[i][2] && ch != 1)
				{
					n = i + 1;
					j = 0;
					output_again(n, j, saved_numbers[i]);
					ch = 1;
				}
			}
		}
		if (prev_alpha < alpha)
		{
			int ch = 0;
			for (int i = 0; i < saved_numbers.size(); ++i)
			{
				if (alpha > saved_numbers[i][2] && ch != 1)
				{
					n = i + 1;
					j = 0;
					output_again(n, j, saved_numbers[i]);
				}
				if (alpha <= saved_numbers[i][2] && ch != 1)
				{
					n = i + 1;
					j = 0;
					output_again(n, j, saved_numbers[i]);
					ch = 1;
				}
			}
		}
	}
	if (alpha == int(alpha))
	{
		if (prev_alpha == alpha)
		{
			for (int i = 0; i < saved_numbers.size(); ++i)
			{
				n = i + 1;
				j = 0;
				output_again(n, j, saved_numbers[i]);
			}
		}
		if (prev_alpha > alpha)
		{
			for (int i = 0; i < alpha; ++i)
			{
				n = i + 1;
				j = 0;
				output_again(n, j, saved_numbers[i]);
			}
		}
		if (prev_alpha < alpha)
		{
			for (int i = 0; i < alpha; ++i)
			{
				n = i + 1;
				j = 0;
				output_again(n, j, saved_numbers[i]);
			}
		}
	}

}

void calc(double alpha, int y, int n, double x, double prev_SN, vector <vector<double>>& saved_numbers)
{
	double a;
	double SN;
	double alphaN;
	if (alpha != int(alpha) && alpha < y) // случай, когда погрешность меньше 1
	{
		do
		{
			a = number_a(n, x);
			SN = number_SN(prev_SN, n, x);
			prev_SN = SN;
			alphaN = number_alphaN(n, x, SN);
			output(n, a, SN, alphaN);
			saved_numbers.push_back({ a, SN, alphaN });
			++n;
		} while (alphaN > alpha);
	}
	if (alpha != int(alpha) && alpha > y) // случай, когда погрешность больше 1
	{
		do
		{
			a = number_a(n, x);
			SN = number_SN(prev_SN, n, x);
			prev_SN = SN;
			alphaN = number_alphaN(n, x, SN);
			output(n, a, SN, alphaN);
			saved_numbers.push_back({ a, SN, alphaN });
			++n;
		} while (alphaN < alpha);
	}
	if (alpha == int(alpha)) // случай, когда происходит выполнение программы определённое количество раз ( n раз )
	{
		while (n <= alpha)
		{
			a = number_a(n, x);
			SN = number_SN(prev_SN, n, x);
			prev_SN = SN;
			alphaN = number_alphaN(n, x, SN);
			output(n, a, SN, alphaN);
			saved_numbers.push_back({ a, SN, alphaN });
			++n;
		}
	}
}

void repeat_calc(double alpha, int y, int n, double x, double prev_SN, double prev_alpha, vector <vector<double>>& saved_numbers)
{
	double a;
	double SN;
	double alphaN;
	if (alpha != int(alpha) && alpha < y) // случай, когда погрешность меньше 1
	{
		if (prev_alpha == alpha) repeat_output(y, prev_alpha, alpha, saved_numbers);
		if (prev_alpha > alpha)
		{
			if (saved_numbers[saved_numbers.size()-1][2] > alpha)
			{
				n = saved_numbers.size() + 1;
				prev_SN = saved_numbers[saved_numbers.size() - 1][1];
				do
				{
					a = number_a(n, x);
					SN = number_SN(prev_SN, n, x);
					prev_SN = SN;
					alphaN = number_alphaN(n, x, SN);
					output(n, a, SN, alphaN); //для отладки
					saved_numbers.push_back({ a, SN, alphaN });
					++n;
				} while (alphaN > alpha);
			}
			repeat_output(y, prev_alpha, alpha, saved_numbers);
		}
		if (prev_alpha < alpha)
		{
			repeat_output(y, prev_alpha, alpha, saved_numbers);
		}
	}
	if (alpha != int(alpha) && alpha > y) // случай, когда погрешность больше 1
	{
		if (prev_alpha == alpha)
			repeat_output(y, prev_alpha, alpha, saved_numbers);
		if (prev_alpha > alpha)
		{
			repeat_output(y, prev_alpha, alpha, saved_numbers);
		}
		if (prev_alpha < alpha)
		{

			if (saved_numbers[saved_numbers.size()-1][2] < alpha)
			{
				n = saved_numbers.size() + 1;
				prev_SN = saved_numbers[saved_numbers.size() - 1][1];
				do
				{
					a = number_a(n, x);
					SN = number_SN(prev_SN, n, x);
					prev_SN = SN;
					alphaN = number_alphaN(n, x, SN);
					output(n, a, SN, alphaN); //для отладки
					saved_numbers.push_back({ a, SN, alphaN });
					++n;
				} while (alphaN < alpha);
			}
			repeat_output(y, prev_alpha, alpha, saved_numbers);
		}
	}
	if (alpha == int(alpha)) // случай, когда происходит выполнение программы определённое количество раз ( n раз )
	{
		if (prev_alpha == alpha) repeat_output(y, prev_alpha, alpha, saved_numbers);
		if (prev_alpha > alpha)
		{
			n = alpha;
			repeat_output(y, prev_alpha, alpha, saved_numbers);
		}
		if (prev_alpha < alpha)
		{
			n = prev_alpha + 1;
			prev_SN = saved_numbers[prev_alpha - 1][1];
			while (n <= alpha)
			{
				if (n > saved_numbers.size())
				{
					a = number_a(n, x);
					SN = number_SN(prev_SN, n, x);
					prev_SN = SN;
					alphaN = number_alphaN(n, x, SN);
					//cout << "This numbers will be calculated" << endl;
					output(n, a, SN, alphaN);
					saved_numbers.push_back({ a, SN, alphaN });
				}
				++n;
			}
			repeat_output(y, prev_alpha, alpha, saved_numbers);
		}
	}
}

int main()
{
	string answer;
	double prev_SN = 0; // объявление переменных, + присваивание предыдущей сумме нулевое значение, чтобы при первой прокрутке программы правильно посчиталась первая частичная сумма
	double prev_x = 0;
	double prev_alpha = 0;
	int prev_n = 0;
	int n = 1;
	vector<vector<double>> saved_numbers;
	do // зацикливание программы
	{
		n = 1;
		string input_x;
		string input_a;
		bool correct_input = false;
		while (correct_input == false) // ввод Х
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
		while (correct_input == false) // ввод погрешности / n, в зависимости от полученных значений
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
		double x = stod(input_x); // перевод строки в число с плавающей точкой
		double alpha = stod(input_a);
		int y = 1;
		if (prev_x != x)
		{
			saved_numbers.clear();
			calc(alpha, y, n, x, prev_SN, saved_numbers);
		}
		if (prev_x == x) repeat_calc(alpha, y, n, x, prev_SN, prev_alpha, saved_numbers);
		cin >> answer;
		cin.ignore();
		prev_SN = 0;
		prev_x = x;
		prev_alpha = alpha;
	} while (answer == "y");
}
