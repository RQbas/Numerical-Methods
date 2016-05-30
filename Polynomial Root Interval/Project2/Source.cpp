#include <iostream>
#include <cstdio>
using namespace std;

void coef_show(float *tab, int number)
{
	for (int i = 0; i<number; i++)
		cout << tab[i] << "\t";
	cout << "\n";
}
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
float horner(float *tab, float *tab_check, int number, float acc, float start_var)
{ 
	tab_check[0] = tab[0];

	int cnt = 1;
	while (1)
	{
		if (tab_check[0] <= 0)
		{
			cout << "First coefficient must be nonnegative";
			break;
		}
	
		for (int i = 1; i < number; i++)
		{
			tab_check[i] = tab_check[i - 1] * start_var +tab[i];
			if (tab_check[i]>0)
				cnt++;
		}
		if (cnt == number)
		{
			break;
		}
		cnt = 1;
		start_var = start_var + acc;
	}
	return start_var;
}
void a_condition(float *tab, float *tab_check, int number)
{
	int k = number - 1;
	
	if ((number-1) % 2 == 1)
	{
		//nieparzyste
		for (int i = 0; i < number; i++) //whole polynomial (-1)^(n)(W_x)
		{
			tab_check[i] = (-1)*tab[i];
		}
		
		for (int i = 0; i < number-1; i++)
		{
			if (k % 2 == 1)
			{
			//	nieparzyste
				tab_check[i] = tab_check[i] * (-1);
			}
			k--;
		}
	}
	else
	{
		//parzyste
		for (int i = 0; i < number; i++)
		tab_check[i] = tab[i];

		for (int i = 0; i < number - 1; i++) //W(-x)
		{
			if (k % 2 == 1)
			{
				//	nieparzyste
				tab_check[i] = tab_check[i] * (-1);
			}
			k--;
		}
	}
}


int main()
{
	int coef_numb;
	float xvalue;
	float acc;

	cout << "Please enter degree of polynomial\n";
	cin >> coef_numb;
	coef_numb++;
	float *tab;
	tab = new float[coef_numb + 1];

	float *tab_check;
	tab_check = new float[coef_numb + 1];

	float *tab_check_a;
	tab_check_a = new float[coef_numb + 1];

	coef_fill(tab, coef_numb);
	cout << "Determine accuracy\n";
	cin >> acc;
	a_condition(tab, tab_check_a, coef_numb);
	float a = horner(tab_check_a, tab_check, coef_numb, acc, -100);
	float b = horner(tab, tab_check, coef_numb, acc, -100);
	cout << "\n\n\n\n Final Interval: <"<<-a<<" , "<<b<<">\n";
		

	system("pause");
}