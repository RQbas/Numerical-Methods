#include <iostream>
#include <cstdio>
#include <math.h>
#include <Windows.h>
#include <inttypes.h>
using namespace std;

void show(float **tab, int tsize)
{
	for (int i = 0; i<tsize; i++)
	{
		for (int j = 0; j<tsize + 1; j++)
		{
			cout << tab[i][j] << " ";
			if (j == tsize - 1)
			{
				cout << "|";
			}
		}
		cout << "\n";
	}
	cout << "\n\n";
}

void fillt(float **tab, int tsize)
{
	float input;
	for (int i = 0; i<tsize; i++)
	{
		cout << "Equation number " << i + 1 << "\n";
		for (int j = 0; j<tsize + 1; j++)
		{
			if (j == tsize)
			{
				cout << "Enter value on the right hand side: ";
				cin >> input;
				tab[i][j] = input;
				cout << "\n";
			}
			else
			{
				cout << "Enter coefficient of " << j + 1 << " variable ";
				cin >> input;
				tab[i][j] = input;
				cout << "\n";
			}
		}


	}
}

void gauss(float **tab, int tsize)
{
	for (int i = 0; i<tsize; i++) {

		double maxEl = abs(tab[i][i]);
		int maxRow = i;
		for (int k = i + 1; k<tsize; k++) {
			if (abs(tab[k][i]) > maxEl) {
				maxEl = abs(tab[k][i]);
				maxRow = k;
			}
		}

		// Swap maximum row with current row (column by column)
		for (int k = i; k<tsize + 1; k++) {
			double tmp = tab[maxRow][k];
			tab[maxRow][k] = tab[i][k];
			tab[i][k] = tmp;
		}

		// Make all rows below this one 0 in current column
		for (int k = i + 1; k<tsize; k++) {
			double c = -tab[k][i] / tab[i][i];
			for (int j = i; j<tsize + 1; j++) {
				if (i == j) {
					tab[k][j] = 0;
				}
				else {
					tab[k][j] += c * tab[i][j];
				}
			}
		}
	}
}

float *var_values(float **tab, int tsize)
{
	float *x;
	x = new float[tsize];
	for (int i = tsize - 1; i >= 0; i--)
	{
		x[i] = tab[i][tsize] / tab[i][i];
		for (int k = i - 1; k >= 0; k--)
		{
			tab[k][tsize] -= tab[k][i] * x[i];
		}
	}
	return x;
}

int main()
{
	_int64 time1, time2, frequency;
	float delta;
	int var_numb;
	cout << "Number of equations: ";
	cin >> var_numb;

	float **matrix = new float*[var_numb + 1];
	for (int i = 0; i<var_numb; i++)
		matrix[i] = new float[var_numb];

	float *x;

	fillt(matrix, var_numb);
	show(matrix, var_numb);

	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	QueryPerformanceCounter((LARGE_INTEGER*)&time1);
	for (int i = 0; i < 1000; i++)
	gauss(matrix, var_numb);
	Sleep(1000);
	QueryPerformanceCounter((LARGE_INTEGER*)&time2);
	delta = (time2 - time1) / (frequency / 1000);
	show(matrix, var_numb);
	cout << "TIME: " << (delta - 1000)/1000 << " ms\n";
	
	x = var_values(matrix, var_numb);
	for (int i = 0; i < var_numb; i++)
		cout << "Variable " << i + 1 << " : " << x[i] << "\n";

	system("pause");
}
