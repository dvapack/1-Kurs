#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <string>

using namespace std;

//вариант 19

bool check_filename(const string& file_name)
{
	if (file_name.empty())
	{
		cout << "Dont try to input empty string!!!!!\n";
		return false;
	}
	if (file_name.size() < 5)
	{
		cout << "Man what are you doing man\n";
		return false;
	}
	if (file_name.find(".txt") != file_name.size() - 4)
	{
		cout << "Wrong file extention! Only .txt files are supported\n";
		return false;
	}
	return true;
}

void censorship(vector<string>& file_content, const string& to_find, const string& to_change)
{
	int k;
	int st_point;
	for (int i = 0; i < file_content.size(); ++i)
	{
		st_point = 0;
		for (int j = 0; j < file_content[i].length(); ++j)
		{
			k = 0;
			int b = j;
			while ((b < file_content[i].length()) && (file_content[i][b] == to_find[k]))
			{
				if (!k)
					st_point = j;
				++k;
				++b;
			}
			if (k == to_find.length())
			{
				file_content[i].erase(st_point, to_find.size());
				file_content[i].insert(st_point, to_change);
				j += (to_change.length() - to_find.length());
			}
		}
	}
}

void file_name_input(string& file_name)
{
	bool check_input;
	do
	{
		cout << "Input a filename > ";
		getline(cin, file_name);
		(check_filename(file_name)) ? check_input = true : check_input = false;
	} while (!check_input);
}

void file_input(vector<string>& file_content, const string& file_name)
{
	string input_string;
	ifstream fin(file_name);
	if (!fin.is_open()) // небольшая проверка на наличие файла
		throw runtime_error("There is no file with this name,");
	while (!fin.eof())
	{
		getline(fin, input_string);
		file_content.push_back(input_string);
	}
}

void strings_input(string& to_find, string& to_change)
{
	cout << "Input a string to find > ";
	getline(cin, to_find);
	cout << "Input a string to change > ";
	getline(cin, to_change);
}



void file_output(vector<string>& file_content, const string& file_name)
{
	ofstream fout(file_name, ios_base::trunc);
	for (int i = 0; i < file_content.size(); ++i)
	{
		fout << file_content[i] << endl;
	}
}

int main()
{
	string restart = "y";
	string file_name;
	string input_string;
	string to_find;
	string to_change;
	cout << "Censorship\n";
	while (restart != "n")
	{
		try
		{
			vector<string> file_content;
			file_name_input(file_name);
			file_input(file_content, file_name);
			strings_input(to_find, to_change);
			censorship(file_content, to_find, to_change);
			file_output(file_content, file_name);
			cout << "Operation has been completed successfully\n";
			cout << "Do you want to continue? (any sumbol/n) > ";
			getline(cin, restart);
		}
		catch (runtime_error& e)
		{
			cout << e.what() << " programm will be restarted\n";
			restart = "y";
		}
	}
}
