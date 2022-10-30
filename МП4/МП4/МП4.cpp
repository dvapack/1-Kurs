#include <iostream>
#include <fstream>
#include <vector>


using namespace std;


void vector_clear(vector <vector<char>>& vector)
{
	for (int i = 0; i < vector.size(); ++i)
	{
		vector[i].clear();
	}
	vector.clear();
}


void changing_letters(vector <vector<char>>& input)
{
	vector <vector<char>> output(input.size());
	cout << endl;
	int not_alpha = 0;
	for (int i = 0; i < input.size(); ++i)
	{
		for (int j = 0; j < input[i].size(); ++j)
		{
			if (!isalpha(input[i][j]))
				++not_alpha;
			output[i].push_back(input[i][j]);
		}
		/*if (output[i].size() > 4)
		{
			for (int j = output[i].size() - 3; j < output[i].size(); ++j)
			{
				output[i][j] = 'x';
			}
		}*/
		if ((output[i].size() - not_alpha) > 4)
		{
			for (int j = output[i].size() - 3 - not_alpha; j < output[i].size() -not_alpha; ++j)
			{
				output[i][j] = 'x';
			}
		}
		not_alpha = 0;

	}
	ofstream fout("output.txt");
	for (int i = 0; i < output.size(); ++i)
	{
		for (int j = 0; j < output[i].size(); ++j)
		{
			fout << output[i][j];
		}
		fout << '\n';
	}
	fout.close();
	vector_clear(output);
}


int main()
{
	char answ;
	char symbol;
	int i = 0;
	int j = 0;
	do
	{
		vector <vector<char>> input;
		input.push_back(vector<char>());
		ifstream fin("test1.txt");
		if (!fin.is_open())
			cout << "This file cant be open!\n";
		else
		{
			cout << "Words in this file: \n\n";
			while ((symbol = fin.get()) != EOF)
			{
				if (symbol != '\n')
					input[i].push_back(symbol);
				else {
					input.push_back(vector<char>());
					++i;
				}
			}
			for (int i = 0; i < input.size(); ++i)
			{
				for (int j = 0; j < input[i].size(); ++j)
				{
					cout << input[i][j];
				}
				cout << endl;
			}
			fin.close();
			cout << endl;
		}
		changing_letters(input);
		ifstream fin2("output.txt");
		if (!fin2.is_open())
			cout << "This file cant be open!\n";
		else
		{
			cout << "Edited words in another file: \n\n";
			while ((symbol = fin2.get()) != EOF)
			{
				cout << symbol;
			}
			fin2.close();
		}
		cout << endl << "If you wanna restart programm input any symbol except 'n' " << endl;
		cin >> answ;
		i = 0;
		j = 0;
		vector_clear(input);
	} while (answ != 'n');
}
