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


void seidel(float **tab, int tsize, float *x)
{
    float *previous_x;
	previous_x = new float[tsize];
	int iteration=0;
	float epsilon;
	float actual_error;
	cout<<"Determine Accuracy: ";
	cin>>epsilon;
	float values;
	float conv_criterion;
	for(int i=0; i<tsize; i++)
    {
        x[i]=0;
        previous_x[i]=0;
    }

	do
    {
        actual_error=0;
        conv_criterion=0;
        for(int i=0; i<tsize; i++)
            {values=0;
            for(int j=0; j<tsize; j++)
            {
                if(j!=i)
            {
                values=values+(tab[i][j]*x[j]);
            }
            }
            x[i]=((tab[i][tsize]-values)/tab[i][i]);

            }
        iteration++;
        for(int i=0; i<tsize; i++)
            {for(int j=0; j<tsize; j++)
                {
                    actual_error+=tab[i][j]*x[j];
                }
                actual_error=fabs(actual_error-tab[i][tsize]);
                }

    for(int i=0; i<tsize; i++)
       {
         conv_criterion+=fabs(x[i]-previous_x[i]);
            previous_x[i]=x[i];
       }
              cout<<iteration<<"->";
    for(int i=0; i<tsize;i++)
    {
        printf("x[%d]:%2f5 ",i+1, x[i]);
    }
    cout<<"\n";
    }
while(epsilon<actual_error || conv_criterion>epsilon);
}

void diagonally_dominant(float **tab, int tsize)
{
    bool Is_DiagonallyDominant=false;
    int cnt=0;
    float sum=0;
    for(int i=0; i<tsize;i++)
    {
        for(int j=0; j<tsize; j++)
        {
            if(i!=j)
            {
               sum+=fabs(tab[i][j]);
            }
        }
        if(fabs(tab[i][i])>=sum)
        {
            cnt++;
        }
        sum=0;
    }
        if(cnt==tsize)
           Is_DiagonallyDominant=true;

    if(Is_DiagonallyDominant)
    {
        cout<<"Matrix is diagonally dominant\n";
    }
    else
    {cout<<"Matrix is not diagonally dominant\n";}
}

float norm(float **tab, int tsize, int case_norm)
{
    float tmp, norm = 0.0;
    float **tab1 = new float*[tsize + 2];
	for (int i = 0; i<tsize; i++)
		tab1[i] = new float[tsize+1];


    for (int i = 0; i<tsize; i++)
	{
		for (int j = 0; j<tsize + 1; j++)
		{
			{
				tab1[i][j]=tab[i][j];
			}
		}
	}
	for (int i = 0; i<tsize; i++)
	{
		for (int j = 0; j<tsize; j++)
		{

				if(i!=j)
                {
                    tab1[i][j]=tab1[i][j]/tab1[i][i];
                }
		}
		tab1[i][i]=0;
	}

   switch (case_norm)
	{
	case 1:
		for (int i = 0; i<tsize; i++) //norm infinity
		{
			tmp = 0;
			for (int j = 0; j<tsize; j++)
				tmp = tmp + fabs(tab1[i][j]);
			if (tmp>norm)
				norm = tmp;

		}
		break;
	case 2:
		for (int j = 0; j<tsize; j++) //norm first
		{
			tmp = 0;
			for (int i = 0; i<tsize; i++)
				tmp = tmp + fabs(tab1[i][j]);
			if (tmp>norm)
				norm = tmp;
		}
		break;
	case 3:
		for (int i = 0; i<tsize; i++) //euclidean norm
			for (int j = 0; j<tsize; j++)
				norm = norm + fabs(tab1[i][j] * tab1[i][j]);
		norm = sqrt(norm);
	}
	return norm;



}
int main()
{
	int var_numb;
	cout << "Number of equations: ";
	cin >> var_numb;

	float **matrix = new float*[var_numb + 2];
	for (int i = 0; i<var_numb; i++)
		matrix[i] = new float[var_numb+1];

	fillt(matrix, var_numb);
	//to store next values
	float *x;
	x = new float[var_numb];
	cout << "\n";

        if(norm(matrix, var_numb, 1)<1 && norm(matrix, var_numb, 2)<1 && norm(matrix, var_numb, 3)<1)
        {
            diagonally_dominant(matrix, var_numb);
            cout<<"Criterion for convergence is satisfied\n";
            cout << "NORMS VALUES: \n";
            cout << "Infinity norm: " << norm(matrix, var_numb, 1) << "\n";
            cout << "First norm: " << norm(matrix, var_numb, 2) << "\n";
            cout << "Euclidean norm: " << norm(matrix, var_numb, 3) << "\n";
            seidel(matrix, var_numb, x);
        }
        else
        {
            diagonally_dominant(matrix, var_numb);
            cout<<"Criterion for convergence is not satisfied\n";
            cout << "NORMS VALUES: \n";
            cout << "Infinity norm: " << norm(matrix, var_numb, 1) << "\n";
            cout << "First norm: " << norm(matrix, var_numb, 2) << "\n";
            cout << "Euclidean norm: " << norm(matrix, var_numb, 3) << "\n";
        }



	system("pause");
}