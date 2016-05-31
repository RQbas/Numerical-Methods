#include <iostream>
#include <cstdio>
#include <math.h>
#include <Windows.h>
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
float gauss(float **tab, int tsize)
{
	int cnt = 0;
	for (int i = 0; i<tsize; i++)
	{

		double maxEl = abs(tab[i][i]);
		int maxRow = i;
		for (int k = i + 1; k<tsize; k++) 
		{
			if (abs(tab[k][i]) > maxEl)
			{
				maxEl = abs(tab[k][i]);
				maxRow = k;
				cnt++;
			}
		}

		// Swap maximum row with current row (column by column)
		for (int k = i; k<tsize + 1; k++) {
			double tmp = tab[maxRow][k];
			tab[maxRow][k] = tab[i][k];
			tab[i][k] = tmp;
			
		}
	
		// Make all rows below this one 0 in current column
		for (int k = i + 1; k<tsize; k++)
		{
			double c = -tab[k][i] / tab[i][i];
			for (int j = i; j<tsize + 1; j++)
			{
				if (i == j) 
				{
					tab[k][j] = 0;
				}
				else {
					tab[k][j] += c * tab[i][j];
					}
			}
		}
	}
	return cnt;
}
float main_determinant(float **tab, int tsize)
{
	float det=1;
	for (int i = 0; i < tsize; i++)
		for (int j = 0; j < tsize; j++)
		{
		if (i == j)
		{
			det *= tab[i][j];
		}
		}
	return det;

}
void coef_cpy(float **tab1, int tsize, float **tab2)
{
	for (int i = 0; i<tsize; i++)
	{
		for (int j = 0; j<tsize + 1; j++)
		{
			tab2[i][j] = tab1[i][j];
		}
	}
}
void column_switch(float **tab, int tsize, int which_column)
{
	float *tmp;
	tmp = new float[tsize];

	for (int i = 0; i<tsize; i++)
	{
		for (int j = 0; j<tsize + 1; j++)
		{
			if (j == which_column)
			{
				tmp[i] = tab[i][j];
				tab[i][j] = tab[i][tsize];
				tab[i][tsize] = tmp[i];
			}
		}
	}

}

int main()
{
int var_numb;
int cntr;
float determinant;
cout << "Number of equations: ";
cin >> var_numb;

float **matrix = new float*[var_numb + 1];
for (int i = 0; i<var_numb; i++)
	matrix[i] = new float[var_numb];


float **matrix_buff = new float*[var_numb + 1];
for (int i = 0; i<var_numb; i++)
	matrix_buff[i] = new float[var_numb];


float *var_det;
var_det = new float[var_numb];



		fillt(matrix, var_numb);
		coef_cpy(matrix, var_numb, matrix_buff);
		
		//CALCULATING MAIN DETERMINANT
		cntr=gauss(matrix, var_numb);
		determinant = pow(-1, cntr)*main_determinant(matrix, var_numb);
		coef_cpy(matrix_buff, var_numb, matrix);

		for (int i = 0; i < var_numb; i++)
		{
			column_switch(matrix, var_numb, i);
			cntr=gauss(matrix, var_numb);
			var_det[i] = pow(-1, cntr)*main_determinant(matrix, var_numb);
			coef_cpy(matrix_buff, var_numb, matrix);
		}

		for (int i = 0; i < var_numb; i++)
		{
			cout << "X_" << i + 1 << ": " << var_det[i] / determinant<<"\n";
		}


system("pause");

}