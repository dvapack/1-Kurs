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
	int work_hours, work_minutes;
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
			day = stoi(check);
			if (day < 0)
				return false;
			month = stoi(check.substr(3, 5));
			if ((month > 12) || (month < 1))
				return false;
			switch (month)
			{
			case 1: case 3: case 5: case 7: case 8: case 10: case 12:
				if (day > 31)
					return false;
				break;
			case 2:
				if (day > 28)
					return false;
				break;
			default:
				if (day > 30)
					return false;
				break;
			}
		}
		else
		{
			end_hour = stoi(check);
			end_minutes = stoi(check.substr(3, 5));
			if ((end_hour > 24) || (end_minutes >= 60))
				return false;
			if (flag == 3)
			{
				start_hour = stoi(prev_string);
				start_minutes = stoi(prev_string.substr(3, 5));
				if ((end_hour < start_hour) || ((end_hour == start_hour) && (end_minutes < start_minutes)))
					return false;
			}
		}
		return true;
	}
	string convert_to_string(const int& first_int, const int& flag, const int& second_int) const
	{
		string str;
		if (first_int < 10)
			str = "0" + to_string(first_int);
		else
			str = to_string(first_int);
		if (flag == 1)
			str.push_back('.');
		else
			str.push_back(':');
		if (second_int < 10)
			str.push_back('0');
		str += to_string(second_int);
		return str;
	}
public:

	WorkTime()
	{
		day = 5;
		month =	5;
		start_hour = 5;
		start_minutes = 5;
		end_hour = 6; 
		end_minutes = 6;
		work_hours = 1;
		work_minutes = 1;
	}

	void time()
	{
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
	}

	WorkTime(const WorkTime& ref_WorkTime)
	{
		this->day = ref_WorkTime.day;
		this->month = ref_WorkTime.month;
		this->start_hour = ref_WorkTime.start_hour;
		this->start_minutes = ref_WorkTime.start_minutes;
		this->end_hour = ref_WorkTime.end_hour;
		this->end_minutes = ref_WorkTime.end_minutes;
		this->work_hours = ref_WorkTime.work_hours;
		this->work_minutes = ref_WorkTime.work_minutes;
	}

	friend ostream& operator<<(ostream& out, const WorkTime& ref);
	friend istream& operator>>(istream& in, WorkTime& ref);
	friend ofstream& operator<<(ofstream& out, const WorkTime& ref);
	friend ifstream& operator>>(ifstream& in, WorkTime& ref);
	bool operator > (const WorkTime& ref)
	{
		int dif = work_hours - ref.work_hours;
		if (dif > 0)
			return true;
		if (dif == 0)
		{
			int min_dif = work_minutes - ref.work_minutes;
			if (min_dif > 0)
				return true;
		}
		else
			return false;
	}
};

ostream& operator<<(ostream& out, const WorkTime& ref)
{
	out << " | date: " << ref.convert_to_string(ref.day, 1, ref.month) << " | start time " << ref.convert_to_string(ref.start_hour, 2, ref.start_minutes) << " | end time "
		<< ref.convert_to_string(ref.end_hour, 2, ref.end_minutes) << " | work time " << ref.convert_to_string(ref.work_hours, 2, ref.work_minutes) << "\n";
	return out;
}

istream& operator>>(istream& in, WorkTime& ref)
{
	int flag;
	string date;
	string start_time;
	string end_time;
	bool check_input = false;
	while (!check_input)
	{
		cout << "Enter date in format day.mnth: ";
		getline(in, date);
		flag = 1;
		if (!ref.check_string(date, flag, start_time))
		{
			cout << "Error! Repeat enter" << endl;
		}
		else
			check_input = true;
	}
	check_input = false;
	while (!check_input)
	{
		cout << "Enter start time in format hr:mnts: ";
		getline(in, start_time);
		flag = 2;
		if (!ref.check_string(start_time, flag, start_time))
		{
			cout << "Error! Repeat enter" << endl;
		}
		else
			check_input = true;
	}
	check_input = false;
	while (!check_input)
	{
		cout << "Enter end time in format hr:mnts: ";
		getline(in, end_time);
		flag = 3;
		if (!ref.check_string(end_time, flag, start_time))
		{
			cout << "Error! Repeat enter" << endl;
		}
		else
			check_input = true;
	}
	return in;
}

ofstream& operator<<(ofstream& out, const WorkTime& ref)
{
	out << " " << ref.convert_to_string(ref.day, 1, ref.month) << " " << ref.convert_to_string(ref.start_hour, 2, ref.start_minutes) << " "
		<< ref.convert_to_string(ref.end_hour, 2, ref.end_minutes) << " " << ref.convert_to_string(ref.work_hours, 2, ref.work_minutes) << "\n";
	return out;
}

ifstream& operator>>(ifstream& in, WorkTime& ref)
{
	int flag;
	string date;
	string start_time;
	string end_time;
	bool check_input = false;
	while (!check_input)
	{
		in >> date;
		flag = 1;
		if (!ref.check_string(date, flag, start_time))
		{
			throw runtime_error("Incorrect date");
		}
		else
			check_input = true;
	}
	check_input = false;
	while (!check_input)
	{
		in >> start_time;
		flag = 2;
		if (!ref.check_string(start_time, flag, start_time))
		{
			throw runtime_error("Incorrect start time");
		}
		else
			check_input = true;
	}
	check_input = false;
	while (!check_input)
	{
		in >> end_time;
		flag = 3;
		if (!ref.check_string(end_time, flag, start_time))
		{
			throw runtime_error("Incorrect end time");
		}
		else
			check_input = true;
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
	Worker(const Worker& ref_Worker)
	{
		this->name = ref_Worker.name;
		this->time = ref_Worker.time;
	}
	string get_name()
	{
		return name;
	}
	friend ostream& operator<<(ostream& out, const Worker& ref);
	friend ofstream& operator<<(ofstream& out, const Worker& ref);
	bool operator > (const Worker& ref)
	{
		if (time > ref.time)
			return true;
		else
			return false;
	}
};

ostream& operator<<(ostream& out, const Worker& ref)
{
	out << "name: " << setw(10) << ref.name;
	out	<< ref.time;
	return out;
}

ofstream& operator<<(ofstream& out, const Worker& ref)
{
	out << setw(7) << ref.name;
	out << ref.time;
	return out;
}



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
			ifstream fin("output.txt");
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
							if (fin.peek() == EOF)
								break;
							buf.clear();
						}
						fin >> name;
						if (!check_name(name))
							throw runtime_error("Incorrect worker name");
						fin >> work_time;
						work_time.time();
						Worker guy(name, work_time);
						workers.push_back(guy);
						correct_flag = 1;
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
				//cout << "name: " << setw(7) << workers[i].get_name() << " | start time: " << workers[i].get_st_time() << " | end time: " << workers[i].get_end_time() << " | work time: " << workers[i].get_time() << endl;
				//cout << workers[i].get_name();
				cout << workers[i];
				if (i)
				{
					if (workers[i] > workers[i - 1])
						cout << "-------\n" << "kamenshchik " << workers[i].get_name() << " works more than previous lent'yai\n" << "-------\n";
				}
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
				//fout << workers[i].get_name() << workers[i].get_st_time() << workers[i].get_end_time() << workers[i].get_time() << endl;
				//fout << workers[i].get_name();
				fout << workers[i];
			}
			fout.close();
		}
		cout << "Do you want to continue? (any symbol/n): ";
		getline(cin, answ);
		cout << endl;
		prev_size = workers.size();
	} while (answ != "n");
}
