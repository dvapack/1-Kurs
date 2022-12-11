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
	string date, start_time, end_time;
	bool check_string(string check, const int& flag, string prev_string)
	{
		int day, month, start_hour, end_hour, start_minutes, end_minutes;
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


public:
	WorkTime()
	{
		date = " 01:01";
		start_time = "12:12";
		end_time = "14:14";
	}

	WorkTime(string dt, string st_t, string en_t)
	{
		this->date = dt;
		this->start_time = st_t;
		this->end_time = en_t;
	}

	WorkTime(const WorkTime& ref_WorkTime)
	{
		this->date = ref_WorkTime.date;
		this->start_time = ref_WorkTime.start_time;
		this->end_time = ref_WorkTime.end_time;
	}

	int get_time()
	{
		int start_hour = stoi(start_time);
		int start_minutes = stoi(start_time.substr(3, 5));
		int end_hour = stoi(end_time);
		int end_minutes = stoi(end_time.substr(3, 5));
		int work_hours, work_minutes;
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
		return work_hours * 60 + work_minutes;
	}

	string convert_work_time()
	{
		string w_t;
		int min = get_time();
		if (min / 60 < 10)
			w_t = "0" + to_string(min / 60);
		else
			w_t = to_string(min / 60);
		w_t.push_back(':');
		if ((min - (min / 60) * 60) < 10)
			w_t.push_back('0');
		w_t += to_string((min - (min / 60) * 60));
		return w_t;
	}
	friend ostream& operator<<(ostream& out, WorkTime& ref);
	friend istream& operator>>(istream& in, WorkTime& ref);
	friend ofstream& operator<<(ofstream& out, WorkTime& ref);
	friend ifstream& operator>>(ifstream& in, WorkTime& ref);

	bool operator > (WorkTime& ref)
	{
		int dif = get_time() - ref.get_time();
		if (dif < 0)
			return false;
		return true;
	}

	bool operator < (WorkTime& ref)
	{
		int dif = get_time() - ref.get_time();
		if (dif > 0)
			return false;
		return true;
	}
};

ostream& operator<<(ostream& out, WorkTime& ref)
{
	out << " | date: " << ref.date << " | start time " << ref.start_time << " | end time "
		<< ref.end_time;
	return out;
}

istream& operator>>(istream& in, WorkTime& ref)
{
	int flag;
	bool check_input = false;
	while (!check_input)
	{
		cout << "Enter date in format day.mnth: ";
		getline(in, ref.date);
		flag = 1;
		if (!ref.check_string(ref.date, flag, ref.start_time))
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
		getline(in, ref.start_time);
		flag = 2;
		if (!ref.check_string(ref.start_time, flag, ref.start_time))
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
		getline(in, ref.end_time);
		flag = 3;
		if (!ref.check_string(ref.end_time, flag, ref.start_time))
		{
			cout << "Error! Repeat enter" << endl;
		}
		else
			check_input = true;
	}
	return in;
}

ofstream& operator<<(ofstream& out, WorkTime& ref)
{
	out << " " << ref.date << " " << ref.start_time << " "
		<< ref.end_time << " ";
	return out;
}

ifstream& operator>>(ifstream& in, WorkTime& ref)
{
	int flag;
	bool check_input = false;
	while (!check_input)
	{
		in >> ref.date;
		flag = 1;
		if (!ref.check_string(ref.date, flag, ref.start_time))
		{
			throw runtime_error("Incorrect date");
		}
		else
			check_input = true;
	}
	check_input = false;
	while (!check_input)
	{
		in >> ref.start_time;
		flag = 2;
		if (!ref.check_string(ref.start_time, flag, ref.start_time))
		{
			throw runtime_error("Incorrect start time");
		}
		else
			check_input = true;
	}
	check_input = false;
	while (!check_input)
	{
		in >> ref.end_time;
		flag = 3;
		if (!ref.check_string(ref.end_time, flag, ref.start_time))
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
	string price;
	WorkTime time;
	bool check_name(string& name)
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

	bool check_money(string& price)
	{
		if (price.empty())
			return false;
		for (int i = 0; i < price.size(); ++i)
		{
			if (!isdigit(price[i]) || isspace(price[i]))
				return false;
		}
		return true;
	}
public:
	Worker()
	{
		name = "Noname";
		price = "100";
	}
	Worker(string name, string price, WorkTime time)
	{
		this->name = name;
		this->price = price;
		this->time = time;
	}
	Worker(const Worker& ref_Worker)
	{
		this->name = ref_Worker.name;
		this->price = ref_Worker.price;
		this->time = ref_Worker.time;
	}
	string get_name()
	{
		return name;
	}
	int day_money()
	{
		return time.get_time() * stoi(price) / 60;
	}
	string to_string_money()
	{
		return to_string(day_money());
	}
	string get_work_time()
	{
		return time.convert_work_time();
	}
	friend ostream& operator<<(ostream& out, Worker& ref);
	friend istream& operator>>(istream& in, Worker& ref);
	friend ofstream& operator<<(ofstream& out, Worker& ref);
	friend ifstream& operator>>(ifstream& in, Worker& ref);
	bool operator > (Worker& ref)
	{
		if (time > ref.time)
			return true;
		else
			return false;
	}
	bool operator < (Worker& ref)
	{
		if (time > ref.time)
			return false;
		else
			return true;
	}
};

ostream& operator<<(ostream& out, Worker& ref)
{
	out << "name: " << setw(7) << ref.name << ' ';
	out << ref.time;
	return out;
}

istream& operator>>(istream& in, Worker& ref)
{
	bool check_input = false;
	while (!check_input)
	{
		//cout << "Enter date in format day.mnth: ";
		getline(in, ref.name);
		if (!ref.check_name(ref.name))
		{
			cout << "Error! Repeat name enter" << endl;
		}
		else
			check_input = true;
	}
	in >> ref.time;
	check_input = false;
	while (!check_input)
	{
		cout << "Enter money: ";
		getline(in, ref.price);
		if (!ref.check_money(ref.price))
		{
			cout << "Error! Repeat money enter" << endl;
		}
		else
			check_input = true;
	}
	//in >> ref.time;
	return in;
}

ofstream& operator<<(ofstream& out, Worker& ref)
{
	out << setw(7) << ref.name << ' ';
	out << ref.time;
	return out;
}

ifstream& operator>>(ifstream& in, Worker& ref)
{
	bool check_input = false;
	while (!check_input)
	{
		in >> ref.name;
		if (!ref.check_name(ref.name))
		{
			throw runtime_error("Incorrect name");
		}
		else
			check_input = true;
	}
	in >> ref.time;
	check_input = false;
	while (!check_input)
	{
		in >> ref.price;
		if (!ref.check_money(ref.price))
		{
			throw runtime_error("Incorrect money");
		}
		else
			check_input = true;
	}
	//in >> ref.time;
	return in;
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


int main()
{
	string answ;
	string choose;
	int input_choice = 0;
	int n_flag = 0;
	int prev_size = 0;
	bool correct_int;
	string amount;
	vector <Worker> workers;
	int correct_flag;
	do
	{
		correct_flag = 0;
		WorkTime work_time;
		Worker guy;
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
				cout << "Please enter " << i + 1 << " worker name: ";
				cin >> guy;
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
						if (!str)
						{
							string buf;
							getline(fin, buf);
							if (fin.peek() == EOF)
								str = 0;
							else
							{
								buf.clear();
								++str;
							}
						}
						while(str)
						{
							fin >> guy;
							workers.push_back(guy);
							//correct_flag = 1;
							--str;
						}
					}
					catch (runtime_error & e)
					{
						cout << e.what() << " in " << str << " string " << endl;
						//correct_flag = 1;
						--str;
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
				cout << workers[i];
				cout << " | money: " << setw(2) << workers[i].to_string_money() << " ";
				cout << "| work time " << workers[i].get_work_time() << "\n";
				if (i)
				{
					if (workers[i] > workers[i - 1])
						cout << "-------\n" << "kamenshchik " << workers[i].get_name() << " works more than previous lent'yai\n" << "-------\n";
					if (workers[i] < workers[i - 1])
						cout << "-------\n" << "lent'yai " << workers[i].get_name() << " works less than previous kamenshchik\n" << "-------\n";
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
				fout << workers[i];
				fout << setw(2) << workers[i].to_string_money() << " ";
				fout << workers[i].get_work_time() << "\n";
			}
			fout.close();
		}
		cout << "Do you want to continue? (any symbol/n): ";
		getline(cin, answ);
		cout << endl;
		prev_size = workers.size();
	} while (answ != "n");
}
