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
	//if (day <1 || day > days_in_month[month - 1])
	// (дни * месяцы * часы * 60 + минуты) этот месяц + предыдущие
	for (int i = 0; i < work_inf.size(); ++i)
	{
		days = stoi(work_inf[i].substr(0, 2));
		month = stoi(work_inf[i].substr(3, 2));
		//minutes[i] = (days * month * stoi(work_inf[i].substr(7, 2)) * 60 + stoi(work_inf[i].substr(10, 2))) + ((days_per_month[month-1] - (days_in_month[month-1] - days))) * 60 + 1;
		minutes[i] = (stoi(work_inf[i].substr(7, 2)) * 60 + stoi(work_inf[i].substr(10, 2))) + ((days_per_month[month - 1] - (days_in_month[month - 1] - days - 1))) * 24 * 60 + 1;
		work_inf[i].clear();
	}
	sort(minutes.begin(), minutes.end());
	for (int i = 1; i < minutes.size(); i += 2)
	{
		minutes[i] = minutes[i] - minutes[i - 1];
		if (minutes[i] > 8 * 60)
			minutes[i] -= (24 - 8 * 60) * (minutes[i] / 6 * 60);
		min += minutes[i];
	}
	minut = to_string(min / 60);
	minut.push_back(':');
	if ((min / 60) < 10)
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
	int i = 0;
	for (int i = 0; i < num; ++i)
		getline(cin, work_inf[i]);
	//for (int i = 0; i < num; ++i)
	//	cout << work_inf[i] << endl;
	cout << work_time(work_inf);
}
