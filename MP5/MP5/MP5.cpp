#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <limits>

int correct_flag = 0;

using namespace std;

class WorkTime
{
private:
	int day, month;
	int start_hour, start_minutes;
	int end_hour, end_minutes;
	string date;
	string start_time;
	string end_time;
	bool check_input;
	int flag;
	int work_hours, work_minutes;
	string work_time;
	bool check_string(string check, const int& flag, string prev_string)
	{
		if (check.size() != 5)
			return false;
		for (int i = 0; i < check.size(); ++i)
		{
			if (!isdigit(check[i]) && (i != 2))
				return false;
			if ((flag == 1) && (i == 2) && (check[i] != '.'))
				return false;
			if (((flag == 2) || (flag == 3)) && (i == 2) && (check[i] != ':'))
				return false;
		}
		if (flag == 1)
		{
			int d = stoi(check);
			if (d < 0)
				return false;
			int m = stoi(check.substr(3, 5));
			if ((m > 12) || (m < 1))
				return false;
			switch (m)
			{
			case 1: case 3: case 5: case 7: case 8: case 10: case 12:
				if (d > 31)
					return false;
				break;
			case 2:
				if (d > 28)
					return false;
				break;
			default:
				if (d > 30)
					return false;
				break;
			}
		}
		else
		{
			int h = stoi(check);
			int mn = stoi(check.substr(3, 5));
			if ((h > 24) || (mn >= 60))
				return false;
			if (flag == 3)
			{
				int pr_h = stoi(prev_string);
				int pr_mn = stoi(prev_string.substr(3, 5));
				if ((h < pr_h) || ((h == pr_h) && (mn < pr_mn)))
					return false;
			}
		}
		return true;
	}
public:

	WorkTime()
	{
		date = "05.05";
		start_time = "05:05";
		end_time = "06:06";
	}

	void time()
	{
		day = stoi(date);
		month = stoi(date.substr(3, 5));
		start_hour = stoi(start_time);
		start_minutes = stoi(start_time.substr(3, 5));
		end_hour = stoi(end_time);
		end_minutes = stoi(end_time.substr(3, 5));
		if (end_minutes < start_minutes)
		{
			work_hours = end_hour - start_hour - 1;
			work_minutes = 60 - start_minutes + end_minutes;
		}
		else
		{
			work_hours = end_hour - start_hour;
			work_minutes = end_minutes - start_minutes;
		}
		if (work_hours < 10)
			work_time = "0" + to_string(work_hours);
		else
			work_time = to_string(work_hours);
		work_time.push_back(':');
		if (work_minutes < 10)
			work_time.push_back('0');
		work_time += to_string(work_minutes);
	}

	WorkTime(const WorkTime& ref_WorkTime)
	{

		this->day = ref_WorkTime.day;
		this->month = ref_WorkTime.month;
		this->start_hour = ref_WorkTime.start_hour;
		this->start_minutes = ref_WorkTime.start_minutes;
		this->end_hour = ref_WorkTime.end_hour;
		this->end_minutes = ref_WorkTime.end_minutes;
		this->date = ref_WorkTime.date;
		this->start_time = ref_WorkTime.start_time;
		this->end_time = ref_WorkTime.end_time;
		this->flag = ref_WorkTime.flag;
		this->work_time = ref_WorkTime.work_time;
		this->work_hours = ref_WorkTime.work_hours;
		this->work_minutes = ref_WorkTime.work_minutes;
	}

	string get_work_date()
	{
		return date;
	}

	string get_start_time()
	{
		return start_time;
	}

	string get_end_time()
	{
		return end_time;
	}

	string get_work_time()
	{
		return work_time;
	}
	friend ostream& operator<<(ostream& out, const WorkTime& ref);
	friend istream& operator>>(istream& in, WorkTime& ref);
	friend ofstream& operator<<(ofstream& out, const WorkTime& ref);
	friend ifstream& operator>>(ifstream& in, WorkTime& ref);
};

ostream& operator<<(ostream& out, const WorkTime& ref)
{
	out << " | date: " << ref.date << " | start time " << ref.start_time << " | end time " << ref.end_time << " | work time " << ref.work_time;
	return out;
}

istream& operator>>(istream& in, WorkTime& ref)
{
	ref.check_input = false;
	while (!ref.check_input)
	{
		cout << "Enter date in format day.mnth: ";
		getline(in, ref.date);
		ref.flag = 1;
		if (!ref.check_string(ref.date, ref.flag, ref.start_time))
		{
			cout << "Error! Repeat enter" << endl;
		}
		else
			ref.check_input = true;
	}
	ref.check_input = false;
	while (!ref.check_input)
	{
		cout << "Enter start time in format hr:mnts: ";
		getline(in, ref.start_time);
		ref.flag = 2;
		if (!ref.check_string(ref.start_time, ref.flag, ref.start_time))
		{
			cout << "Error! Repeat enter" << endl;
		}
		else
			ref.check_input = true;
	}
	ref.check_input = false;
	while (!ref.check_input)
	{
		cout << "Enter end time in format hr:mnts: ";
		getline(in, ref.end_time);
		ref.flag = 3;
		if (!ref.check_string(ref.end_time, ref.flag, ref.start_time))
		{
			cout << "Error! Repeat enter" << endl;
		}
		else
			ref.check_input = true;
	}
	return in;
}

ofstream& operator<<(ofstream& out, const WorkTime& ref)
{
	out << " | date: " << ref.date << " | start time " << ref.start_time << " | end time " << ref.end_time << " | work time " << ref.work_time << "\n";
	return out;
}

ifstream& operator>>(ifstream& in, WorkTime& ref)
{
	ref.check_input = false;
	while (!ref.check_input)
	{
		in >> ref.date;
		ref.flag = 1;
		if (!ref.check_string(ref.date, ref.flag, ref.start_time))
		{
			throw runtime_error("Incorrect date");
		}
		else
			ref.check_input = true;
	}
	ref.check_input = false;
	while (!ref.check_input)
	{
		in >> ref.start_time;
		ref.flag = 2;
		if (!ref.check_string(ref.start_time, ref.flag, ref.start_time))
		{
			throw runtime_error("Incorrect start time");
		}
		else
			ref.check_input = true;
	}
	ref.check_input = false;
	while (!ref.check_input)
	{
		in >> ref.end_time;
		ref.flag = 3;
		if (!ref.check_string(ref.end_time, ref.flag, ref.start_time))
		{
			throw runtime_error("Incorrect end time");
		}
		else
			ref.check_input = true;
	}
	return in;
}

class Worker
{
private:
	string name;
	WorkTime time;
public:
	Worker()
	{
		name = "Noname";
	}
	Worker(string name, WorkTime time)
	{
		this->name = name;
		this->time = time;
	}
	string get_name()
	{
		return name;
	}
	string get_st_time()
	{
		return time.get_start_time();
	}
	string get_end_time()
	{
		return time.get_end_time();
	}
	string get_time()
	{
		return time.get_work_time();
	}
};

bool check_amount(string amount)
{
	if ((amount.empty()) || (amount.size() > 100))
		return false;
	for (int i = 0; i < amount.size(); ++i)
	{
		if (!isdigit(amount[i]) || isspace(amount[i]))
			return false;
	}
	int am = stoi(amount);
	if (am <= 0)
		return false;
	return true;
}

bool check_int(string input)
{
	if ((input.empty()) || ((input != "0") && (input != "1")))
		return false;
	return true;
}

bool check_name(string name)
{
	if (name.empty())
		return false;
	for (int i = 0; i < name.size(); ++i)
	{
		if (!isalpha(name[i]) || isspace(name[i]))
			return false;
	}
	return true;
}


int main()
{
	string answ;
	string choose;
	int input_choice = 0;
	int n_flag = 0;
	int prev_size = 0;
	bool correct_int;
	string name;
	string amount;
	vector <Worker> workers;
	int correct_flag;
	do
	{
		correct_flag = 0;
		WorkTime work_time;
		correct_int = false;
		while (!correct_int)
		{
			cout << "Where do you want to read information? For console enter 0, for text file - 1: ";
			getline(cin, choose);
			if (!check_int(choose))
				cout << "Error! Please enter 0 or 1" << endl;
			else
				correct_int = true;
		}
		input_choice = stoi(choose);
		correct_int = false;
		if (!input_choice)
		{
			correct_int = false;
			while (!correct_int)
			{
				cout << "Enter amount of workers you want to add: ";
				getline(cin, amount);
				if (!check_amount(amount))
				{
					cout << "Error! Please enter correct amount" << endl;
				}
				else
					correct_int = true;
			}
			int am = stoi(amount) + prev_size;
			workers.resize(am);
			for (int i = prev_size; i < workers.size(); ++i)
			{
				correct_int = false;
				while (!correct_int)
				{
					cout << "Please enter " << i + 1 << " worker name: ";
					getline(cin, name);
					if (!check_name(name))
						cout << "Error! Please enter correct name" << endl;
					else
					{
						correct_int = true;
					}
				}
				correct_int = false;
				cin >> work_time;
				work_time.time();
				cout << "name: " << name << work_time << endl;
				Worker guy(name, work_time);
				workers[i] = guy;
			}
		}
		else
		{
			workers.clear();
			ifstream fin("test1.txt");
			if (!fin.is_open()) // небольшая проверка на наличие файла
			{
				throw runtime_error("This file cant be opened");
			}
			else
			{
				int str = 1;
				while (!fin.eof())
				{
					try
					{
						if (correct_flag)
						{
							string buf;
							getline(fin, buf);
							buf.clear();
						}
						fin >> name;
						if (!check_name(name))
							throw runtime_error("Incorrect worker name");
						fin >> work_time;
						work_time.time();
						Worker guy(name, work_time);
						workers.push_back(guy);
						correct_flag = 0;
						++str;
					}
					catch (runtime_error& e)
					{
						cout << e.what() << " in " << str << " string " << endl;
						correct_flag = 1;
						++str;
					}
				}
				fin.close();
			}
		}
		correct_int = false;
		while (!correct_int)
		{
			cout << "Where do you want to output information? For console enter 0, for text file - 1: ";
			getline(cin, choose);
			if (!check_int(choose))
				cout << "Error! Please enter 0 or 1" << endl;
			else
				correct_int = true;
		}
		input_choice = stoi(choose);
		if (!input_choice)
		{
			cout << "all workers: \n";
			for (int i = 0; i < workers.size(); ++i)
			{
				cout << "name: " << setw(7) << workers[i].get_name() << " | start time: " << workers[i].get_st_time() << " | end time: " << workers[i].get_end_time() << " | work time: " << workers[i].get_time() << endl;
			}
		}
		else
		{
			ofstream fout("output.txt");
			if (!fout.is_open()) // небольшая проверка на наличие файла
			{
				throw runtime_error("This file cant be opened");
			}
			for (int i = 0; i < workers.size(); ++i)
			{
				fout << "name: " << setw(10) << workers[i].get_name() << " | start time: " << workers[i].get_st_time() << " | end time: " << workers[i].get_end_time() << " | work time: " << workers[i].get_time() << endl;
			}
			fout.close();
		}
		cout << "Do you want to continue? (any symbol/n): ";
		getline(cin, answ);
		cout << endl;
		prev_size = workers.size();
	} while (answ != "n");
}
