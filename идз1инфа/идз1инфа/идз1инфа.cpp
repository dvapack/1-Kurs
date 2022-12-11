#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string work_time(vector <string>& work_inf)
{
	int days_in_month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int days_per_month[12] = { 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
	int days, month;
	int min = 0;
	string minut;
	vector <int> minutes(work_inf.size());
	// находим для каждой даты сколько минут с начала года он работал ( допустим с начала года до 15.01. 17:00 он работал 8220 минут, а до 16.01. 12:00 8400 минут, следовательно между этими датами время работы 180 минут )
	for (int i = 0; i < work_inf.size(); ++i)
	{
		days = stoi(work_inf[i].substr(0, 2));
		month = stoi(work_inf[i].substr(3, 2));
		minutes[i] = (stoi(work_inf[i].substr(7, 2)) * 60 + stoi(work_inf[i].substr(10, 2))) + ((days_per_month[month - 1] - (days_in_month[month - 1] - days))) * 8 * 60;
	}
	sort(minutes.begin(), minutes.end());
	for (int i = 1; i < minutes.size(); i += 2)
	{
		minutes[i] -= (minutes[i - 1] - 1); // тут прибавляем минуту потому что оказывается начинает он в 17:00:00, а заканчивает в 12:00:59, грубо говоря минута сверху просто накидывается))
		min += minutes[i];
	}
	minut = to_string(min / 60);
	minut.push_back(':');
	if ((min - (min / 60) * 60) < 10)
		minut.push_back('0');
	minut += to_string((min - (min / 60) * 60));
	return minut;
}


int main()
{
	string n;
	getline(cin, n);
	int num = stoi(n);
	vector <string> work_inf(num);
	for (int i = 0; i < num; ++i)
		getline(cin, work_inf[i]);
	cout << work_time(work_inf);
}
