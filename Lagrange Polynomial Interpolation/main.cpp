#include <iostream>
#include <cstdio>
#include <vector>
#include <math.h>
#include <cstdlib>
using namespace std;

float *horner_value(float *tab1, float var, int tab1_size) //horner scheme used in polynomial division
{
     float *prod = new float[tab1_size];
    prod[0] = tab1[0];

        for (int i = 1; i<tab1_size; i++)
            prod[i] = prod[i-1]*var +tab1[i];
        return prod;
}

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


int main()
{
    int n_node; //number of nodes
    float buffor; //buffor for user input

                cout<<"Number of nodes ";
                cin>>n_node;
    float *x_node;  //table containing x coordinates
    float *y_node;  //table containing y coordinates
    float *final_tab;  //table final coefficients of polynomial

    x_node= new float[2*n_node]; //creating arrays with number of nodes spots
    y_node= new float[n_node];
    final_tab= new float[n_node+1];

    for(int i=0; i<2*n_node; i++)
        x_node[i]=1;                    //fullfiling x coordinates array with 1 (coefficient of x in (x-2) where 2 is in x_node array
    for(int i=0; i<n_node+1; i++)
        final_tab[i]=0;    //fullfiling final table with zero -> necessary later to use += operator


        for(int i=0; i<n_node; i++) //fullfining user data
        {
                cout<<"x coordinate for "<<i+1<<"\n";
                cin>>buffor;
            x_node[2*i+1]=-buffor;   //x coordinate for e.g. {1, 2, 4} -> [1, 1, 1, 2, 1, 4]
                cout<<"y coordinate for "<<i+1<<"\n";
                cin>>buffor;
            y_node[i]=buffor; //y coordinates
        }

        float *buff_tab;   //buffor array keeping multiplied polynomials

        float *buff_tab2;
        buff_tab2= new float[n_node+1]; //buffor array keeping multiplied polynomials to avoid overwriting

        float coefficient;  //simple coefficient in front of polynomial
        float denominator=1; //denominator under polynomial part



        float *mult_tab1;   //1-st table to store coordinates to initially perform polynomial multiplication
        mult_tab1= new float[1];

        float *mult_tab2; //2nd table to store coordinates to perform polynomial multiplication
        mult_tab2= new float[1];



    for(int k=0; k<n_node; k++) //for every part of formula (division of formula into n_node parts
    {
        for(int i=0; i<n_node-1; i++) //for every multiplication operation
           {
            if(i==0) //when we just started multiplication
                {
                    mult_tab1[0]=x_node[0]; //we set 1st multiplication components (1, 5 in [1, 5, 1, 4])
                    mult_tab1[1]=x_node[1];

                    mult_tab2[0]=x_node[2]; //we set 2nd multiplication components (1, 4 in [1, 5, 1, 4])
                    mult_tab2[1]=x_node[3];
                        buff_tab=multiply(mult_tab1, mult_tab2, i+2, 2); //perform multiplication
                        for(int j=0; j<n_node+1; j++)
                            buff_tab2[j]=buff_tab[j];  //fullfill buffor to store coefficients
                }
                else
                {
                    mult_tab2[0]=x_node[2*i+2]; //when it's not first operation we use only second buffor and previous buffor for coefficients (buff_tab2)
                    mult_tab2[1]=x_node[2*i+3];
                        buff_tab=multiply(buff_tab2, mult_tab2, i+2 ,2); //multiply buffor mult_tab2 with buffor storing coeff. buff_tab2 and store it in buff_tab
                        for(int j=0; j<n_node+1; j++)
                        {
                            buff_tab2[j]=buff_tab[j]; //again rewriting to buff_tab2 to free buff_tab
                        }
                }
           }

            buff_tab2=horner_value(buff_tab2, -(x_node[(2*k+1)]), n_node+1); //now we divide using horner scheme by unwanted polynomial denoted by actual 'k' position (polynomial number k)
                cout<<"Numerator polynomial: ";
            for(int i=0; i<n_node; i++) //writing partial polynomials
                {
                    cout<<buff_tab2[i]<<"x^"<<n_node-1-i;
                        if(buff_tab2[i]>=0 && (n_node-1)!=i)
                            cout<<" + ";
                        if(buff_tab2[i]<0)
                            cout<<" ";
                }

            for(int i=0; i<n_node; i++) //calculating denominator under polynomial
            {
                if((-x_node[2*k+1]+x_node[2*i+1])!=0)//condition which gets rid of unwanted difference (e.g. x_node[k]-x_node[k]) which would equal 0 and crash program
                {
                     denominator*=(-x_node[2*k+1]+x_node[2*i+1]);  //multiplying differences
                }

            }
            coefficient=y_node[k]/denominator;  //coefficient in front of polynomial y coordinate / denominator
                for(int i=0; i<n_node; i++)
                {
                    final_tab[i]+=coefficient*buff_tab2[i]; //fullfiling table of final coefficients [summing for all k polynomials since it's still in for loop with k conditions
                }
            denominator=1; //cleaning denominator
            cout<<" Multiply Coefficient: "<<coefficient<<" \n";
        }




        cout<<"Final formula: "; //writing final formula
        for(int i=0; i<n_node; i++)
            {
            cout<<final_tab[i]<<"x^"<<(n_node-1)-i;
            if(final_tab[i+1]>=0 && (n_node-1)!=i)
                cout<<" + ";
            if(final_tab[i+1]<0)
                cout<<" ";
            }
    getchar();
    cout<<"\n\n";
    system("pause");
}
