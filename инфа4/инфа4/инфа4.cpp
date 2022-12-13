#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <string>

using namespace std;


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

int main()
{
	string restart;
	string file_name;
	string input_string;
	string to_find;
	string to_change;
	bool check_input;
	cout << "Censorship\n";
	do
	{
		vector<string> file_content;
		try
		{
			do
			{
				cout << "Input a filename > ";
				getline(cin, file_name);
				(check_filename(file_name)) ? check_input = true : check_input = false;
			} while (!check_input);
			ifstream fin(file_name);
			if (!fin.is_open()) // небольшая проверка на наличие файла
				throw runtime_error("There is no file with this name,");
			cout << "Input a string to find > ";
			getline(cin, to_find);
			cout << "Input a string to change > ";
			getline(cin, to_change);
			while (!fin.eof())
			{
				getline(fin, input_string);
				file_content.push_back(input_string);
			}
			fin.close();
			censorship(file_content, to_find, to_change);
			ofstream fout(file_name, ios_base::trunc);
			for (int i = 0; i < file_content.size(); ++i)
			{
				fout << file_content[i] << endl;
			}
			cout << "Operation has been completed successfully\n";
			cout << "Do you want to continue? (any sumbol/n) > ";
			getline(cin, restart);
		}
		catch (runtime_error& e)
		{
			cout << e.what() << " programm will be restarted\n";
			restart = "y";
		}
	} while (restart != "n");
}
