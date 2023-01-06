#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


void input_saved_info(vector <int>& saved_info)
{
	string buff_string;
	fstream fin("saved.txt");
	while (!fin.eof())// чтение файла
	{
		getline(fin, buff_string);
		saved_info.push_back(stoi(buff_string));
	}
	fin.close();
}


void input(vector <int>& saved_info, int& current_date)
{
	int buff;
	cout << "Enter current day: ";
	cin >> buff;
	current_date = buff;
	cout << "Enter amount of written pages today: ";
	cin >> buff;
	saved_info[0] += buff;
	cout << "Enter amount of learned pages today: ";
	cin >> buff;
	saved_info[1] += buff;
	cout << "Enter amount of watched lections today: ";
	cin >> buff;
	saved_info[2] += buff;
	cout << "Enter amount of watched videos today: ";
	cin >> buff;
	saved_info[3] += buff;
}


void magic(int& exam_date, int& current_date, const vector <int>& saved_info)
{
	int days = exam_date - current_date;
	cout << "Current result is: \n";
	cout << "Days left: " << days << endl;
	cout << "Percentage of written pages: " << double((100 * saved_info[0]) / 304) << '%' << endl;
	cout << "Percentage of learned pages: " << double((100 * saved_info[1]) / saved_info[0]) << '%' << endl;
	cout << "Percentage of watched lections: " << double((100 * saved_info[2]) / 20) << '%' << endl;
	cout << "Percentage of watched videos: " << double((100 * saved_info[3]) / 31) << '%' << endl;
}

void saving_info(const vector <int>& saved_info)
{
	fstream fout("saved.txt");
	for (int i = 0; i < 4; ++i)
	{
		if (i == 3)
			fout << saved_info[i];
		else
			fout << saved_info[i] << endl;
	}
	fout.close();
}

int main()
{
	int exam_date = 20;
	int current_date;
	vector <int> saved_info;
	cout << "This programm shows your current progress of preparation to exam\n";
	input_saved_info(saved_info);
	input(saved_info, current_date);
	saving_info(saved_info);
	magic(exam_date, current_date, saved_info);
}
