
#include<stdio.h>
#include <cstdio>
#include<math.h>
#include <iostream>
using namespace std;

float *multiply(float *tab1, float *tab2, int tab1_size, int tab2_size) //multiplication of polynomial (polynomial*polynomial)
{
   float *prod = new float[tab2_size+tab1_size-1];
   for (int i = 0; i<tab2_size+tab1_size-1; i++)
     prod[i] = 0;

   for (int i=0; i<tab1_size; i++)
   {
     for (int j=0; j<tab2_size; j++)
         prod[i+j] += tab1[i]*tab2[j];
   }
   return prod;
}

float *horner_value(float *tab1, float var, int tab1_size) //horner scheme used in polynomial division
{
     float *prod = new float[tab1_size];
    prod[0] = tab1[0];
        for (int i = 1; i<tab1_size; i++)
            prod[i] = prod[i-1]*var +tab1[i];
        return prod;
}

void flip(float *tab, int size)
{
    float *buff;
    buff= new float[size];
    int k=size-1;
    for(int i=0; i<size; i++)
    {
        buff[i]=tab[i];
    }
    for(int i=0; i<size; i++)
    {
        tab[k]=buff[i];
        k--;
    }
}
void shift(float *tab, int size)
{
    float x;
    for(int i=0; i<size; i++)
    {

        if(i==size-1)
        {
            tab[i]=0;
        }
        else
            {x=tab[i+1];
            tab[i]=x;

            }
    }
}



int main()

{

    int n; //number of nodes
    float buffor; //buffor variable for user's input
        cout<<"Number of nodes: ";
        cin>>n;

    float *x; //array of x coordinates
    x = new float[n];

    float **y= new float*[n+1]; //double array for y coordinates & newton divided differences
    for(int i=0; i<n+1; i++)
        y[i]= new float[n];

     for(int i=0; i<n; i++) //fullfining user data
        {
                cout<<"x coordinate for "<<i+1<<"\n";
                cin>>buffor;
            x[i]=buffor;
                cout<<"y coordinate for "<<i+1<<"\n";
                cin>>buffor;
            y[0][i]=buffor;
        }

int k;
        for(int i=1;i<n;i++) //calculating divided differences (f(x1)-f(x0))/(x1-x0) etc
            {
                k=i;
                for(int j=0;j<n-i;j++)
                {
                    y[i][j]=(y[i-1][j+1]-y[i-1][j])/(x[k]-x[j]);
                    k++;
                }
            }
        cout<<"DIFFERENCE TABLE\n";
//display Forward Difference Table


    for(int i=0;i<n;i++)
    {
        cout<<x[i]<<"\t";
        for(int j=0;j<(n-i);j++)
            cout<<y[j][i]<<"\t";
        cout<<"\n";
    }
    cout<<"Polynomials from the highest order\n";
    cout<<"P.coef - Polynomial coefficients\n";
    cout<<"P.coef.m - Polynomial coefficients after scalar multiplication\n";

    float *coeff_tab; //array for coefficients
    coeff_tab= new float[n];

for(int j=0; j<n; j++)
        {
            coeff_tab[j]=y[j][0];
        }
    cout<<"Scalars: ";
for(int j=0; j<n; j++)
        {
            cout<<coeff_tab[j]<<" ";
        }

    float *mult_tab;
    mult_tab= new float[2*n];

    for(int i=0; i<2*n; i++)
   {
       mult_tab[i]=1;
       if(i%2==1)
       {
        mult_tab[i]=-x[(i-1)/2];
       }
   }

    float *final_tab;
    final_tab=new float[n+1];

    for(int j=0; j<n+1; j++)
            {
        final_tab[j]=0;
            }


        float *buff_tab;
        float *buff_tab2;

        buff_tab2= new float[n+1];

        float *mult_tab1;   //1-st table to store coordinates to initially perform polynomial multiplication
        mult_tab1= new float[1];

        float *mult_tab2; //2nd table to store coordinates to perform polynomial multiplication
        mult_tab2= new float[1];

  for(int i=0; i<n-2; i++) //for every multiplication operation
           {
            if(i==0) //when we just started multiplication
                {
                    mult_tab1[0]=mult_tab[0]; //we set 1st multiplication components (1, 5 in [1, 5, 1, 4])
                    mult_tab1[1]=mult_tab[1];

                    mult_tab2[0]=mult_tab[2]; //we set 2nd multiplication components (1, 4 in [1, 5, 1, 4])
                    mult_tab2[1]=mult_tab[3];
                        buff_tab=multiply(mult_tab1, mult_tab2, i+2, 2); //perform multiplication
                        for(int j=0; j<n; j++)
                            buff_tab2[j]=buff_tab[j];  //fullfill buffor to store coefficients
                }
                else
                {
                    mult_tab2[0]=mult_tab[2*i+2]; //when it's not first operation we use only second buffor and previous buffor for coefficients (buff_tab2)
                    mult_tab2[1]=mult_tab[2*i+3];
                        buff_tab=multiply(buff_tab2, mult_tab2, i+2 ,2); //multiply buffor mult_tab2 with buffor storing coeff. buff_tab2 and store it in buff_tab
                        for(int j=0; j<n; j++)
                        {
                            buff_tab2[j]=buff_tab[j]; //again rewriting to buff_tab2 to free buff_tab

                        }
                }

           }

        for(int j=0; j<n; j++)
            {
                final_tab[j]=(coeff_tab[n-1])*buff_tab2[j]; //first implementation of scalar*polynomial coefficients
            }

        cout<<"\n";
        cout<<"P.coef  ";

        for(int j=0; j<n; j++)
            {
                cout<<buff_tab2[j]<<"\t";
            }
            cout<<"\n";
            cout<<"P.coef.m ";

            for(int j=0; j<n; j++)
            {
                cout<<final_tab[j]<<"\t";

            }

            cout<<"\n\n\n";

    float *buffcpy; //buffor copying buff_tab2 to perform correct degree shifting (to not mess with division)
    for(int i=n-1; i>0; i--)
    {
        buff_tab2=horner_value(buff_tab2, (-mult_tab[(2*i-1)]), n);
        buffcpy=buff_tab2;
        flip(buffcpy, n);
        shift(buffcpy, n);
        flip(buff_tab2, n);
        cout<<"P.coef ";
          for(int j=0; j<n; j++)
            {
                cout<<buffcpy[j]<<"\t";
                final_tab[j]+=(coeff_tab[i-1])*buffcpy[j];
            }
                cout<<"\n";
                cout<<"P.coef.m ";
            for(int j=0; j<n; j++)
            {
                cout<<final_tab[j]<<"\t";
            }
                flip(buffcpy, n);
                flip(buff_tab2, n);
        cout<<"\n\n";
    }
        cout<<"\n\n";
        cout<<"Final formula: "; //writing final formula

        for(int i=0; i<n; i++)
            {
            cout<<final_tab[i]<<"x^"<<(n)-1-i;
            if(final_tab[i+1]>=0 && (n-1)!=i)
                cout<<" + ";
            if(final_tab[i+1]<0)
                cout<<" ";
            }
    getchar();
    system("pause");
return 0;
}
