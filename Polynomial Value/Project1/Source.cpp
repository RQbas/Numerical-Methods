#include <iostream>
#include <cstdio>
#include <cstring>
#include <string.h>
#include <sstream>
#include <chrono>
#include <Windows.h>
using namespace std;

void coef_fill(float *tab, int number)
{
	float buff;
	int cnt = 0;
	while (cnt<number)
	{
		if (cnt == 0)
		{
			cout << "Please enter highest coefficient\n";
		}
		else
		{
			if (cnt == 1)
				cout << "Please enter " << cnt + 1 << "nd coefficient\n";
			if (cnt == 2)
				cout << "Please enter " << cnt + 1 << "rd coefficient\n";
			if (cnt>2)
				cout << "Please enter " << cnt + 1 << "th coefficient\n";
		}
		cin >> buff;
		tab[cnt] = buff;
		cnt++;
	}

}
void coef_show(float *tab, int number)
{
	for (int i = 0; i<number; i++)
		cout << tab[i] << "\t";
	cout << "\n";
}
float normal_value(float *tab, int number, float xvalue)
{
	float result = 0;
	int quotient_result = 1;
	int k = number - 1;

	for (int i = 0; i<number - 1; i++)
	{

		for (int j = k; j>0; j--)
		{
			quotient_result = quotient_result*xvalue;
		}
		k--;
		result = result + (tab[i] * quotient_result);
		quotient_result = 1;
	}


	result = result + tab[number - 1];
	return result;
}
float horner_value(float *tab, int number, float xvalue)
{
	float res = tab[0];

		for (int i = 1; i<=number-1; i++)
			res = res*xvalue +tab[i];

		return res;
	
}
int main()
{
	//Variables
	int coef_numb;
	float xvalue;
	string user_decision;
	_int64 time1, time2, delta, frequency;
	cout << "Please enter degree of polynomial\n";
	cin >> coef_numb;
	coef_numb++;
	float *tab;
	tab = new float[coef_numb + 1];


	//Procedures
	coef_fill(tab, coef_numb);

	
	string dec = "y";
	while (dec=="y")
	{
		cout << "Choose method of value calculation:\n h - Horner\n s - Standard\n";
		cin >> user_decision;
		while (user_decision != "h" && user_decision != "s")
		{
			cout << "Wrong pick. Repeat \n";
			user_decision = "";
			cin >> user_decision;
		}
		if (user_decision == "h")
		{
			cout << "Please enter value of x\n";
			cin >> xvalue;

			QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
			QueryPerformanceCounter((LARGE_INTEGER*)&time1);

			cout << "RESULT: " << horner_value(tab,coef_numb,xvalue)<<"\n";
			Sleep(1000);
			QueryPerformanceCounter((LARGE_INTEGER*)&time2);
			delta = (time2 - time1) / (frequency / 1000);
			
				
							
				cout << " TIME: " << delta-1000 <<"ms"<< "\n";
			
			cout << "Back to decision - y | n\n";
			cin >> dec;
		}
		if (user_decision == "s")
		{
			cout << "Please enter value of x\n";
			cin >> xvalue;

			QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
			QueryPerformanceCounter((LARGE_INTEGER*)&time1);


			cout << "RESULT: " << normal_value(tab, coef_numb, xvalue)<<"\n";

			Sleep(1000);
			QueryPerformanceCounter((LARGE_INTEGER*)&time2);
			delta = (time2 - time1) / (frequency / 1000);

			cout << " TIME: " << delta-1000<<"ms" << "\n";
			cout << "Back to decision - y | n\n";
				cin >> dec;
		}
	}
	system("pause");
	return 0;
}
