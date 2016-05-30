#include <iostream>
#include <cstdio>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <cmath>
using namespace std;

class input
{
    public:
    int n1;
    long double h;
    long double x0;
    void fill_input()
    {
        cout<<"Insert n number: \n";
        cin>>n1;
        cout<<"Insert step (h): \n";
        cin>>h;
        cout<<"Insert x0: \n";
        cin>>x0;
    }
    input()
    {
        fill_input();
    }


};
class final_formula: public input
{
    public:
    long double **tab;
    long double *tabvalues;
    long double **init_fullfill(int s);
    void show_matrix();
    long double getn1() const
    {
     return input::n1;
    }
     long double geth()
    {
     return input::h;
    }
    long double getx0()
    {
     return input::x0;
    }
    void backward_diff(int s)
    {
    for(int j=1;j<s+1;j++)
        for(int i=s;i>(j-1);i--)
            tab[i][j] = tab[i][j-1] - tab[i-1][j-1];
    }
    void ToVector(int s)
    {
    tabvalues= new long double[s];
    for(int i=0; i<s; i++)
    {
        tabvalues[i]=tab[s][i+1];
    }
    }
    final_formula()
        {
        tab=init_fullfill(n1);
        backward_diff(n1);
        ToVector(n1);
        }


};
long double **final_formula::init_fullfill(int s)
{
     {
        long double **tab1=new long double*[s+1];
            for(int i=0; i<(s+1); i++)
                tab1[i]= new long double[s+1];
        for(int i=0; i<s+1; i++)
        {
            for(int j=0; j<s+1; j++)
            {
                tab1[i][j]=0;
            }
            tab1[i][0]=x0;
        }
        int k=s;
        long double arg;
        for(int i=0; i<s+1; i++)
        {
                arg=(long double) (tab1[i][0]-(k*h));
                tab1[i][0]=arg*arg-arg+1;
                k--;
        }
        return tab1;
    }
}

void final_formula::show_matrix()
{
    printf("\n***********Backward Difference Table ***********\n");
    for(int i=0;i<n1+1;i++)
    {
        for(int j=0;j<=i;j++)
            printf("\t    %.6f",tab[i][j]);
        printf("\n");
    }

}




//----------------------------------//

void show(long double *tab, int size)
{
    for(int i=0; i<size; i++)
        cout<<tab[i]<<" ";
    cout<<"\n";
}

long double *second_order(long double *tab1, int tab1_size) //multiplication of polynomial (polynomial*polynomial)
{
   long double *prod = new long double[tab1_size+tab1_size-1];
   long double *prod1 = new long double[tab1_size+tab1_size-1];
   for (int i = 0; i<tab1_size+tab1_size-1; i++)
     prod[i] = 0;

   for (int i=0; i<tab1_size; i++)
   {
     for (int j=0; j<tab1_size; j++)
         prod[i+j] += tab1[i]*tab1[j];
   }
    prod1[0]=0;
    for(int i=1; i<2*tab1_size-1 ;i++)
        prod1[i]=prod[i-1];
   return prod1;
}

void first_order(long double *tab, int size)
{
    for(int i=0; i<size; i++)
    {
        tab[i]=(1.0/(1.0+i));

    }
}

long double value_derivative_first(long double *values, long double *coeff, long double h, long double n)
{
long double part_val=0;
for(int i=0; i<n; i++)
    part_val+=values[i]*coeff[i];
    return (1/h)*part_val;
}
long double value_derivative_second(long double *values, long double *coeff, long double h, long double n)
{
long double part_val=0;
for(int i=0; i<n; i++)
    part_val+=values[i]*coeff[i];
    return (1/(h*h))*part_val;
}
long double derivative_first(long double arg)
{
    return 2*arg-1;
}
long double derivative_second(long double arg)
{
    return 2.0;
}
void SearchMax(long double *tab1, long double *tab2, long double *tab3, long double *tab4,int size)
{
    long double max1=tab1[0], max2=tab2[0], max3=tab3[0], max4=tab4[0];;
    int index1, index2, index3, index4;
    for(int i=1; i<size; i++)
        {if(tab1[i]>max1)
            {max1=tab1[i];
            index1=i;
            }
        if(tab2[i]>max2)
        {
            max2=tab2[i];
            index2=i;
        }
        if(tab3[i]>max3)
            {max3=tab3[i];
            index3=i;
            }
            if(tab4[i]>max4)
            {max4=tab4[i];
            index4=i;
            }
        }
        cout<<"Maximum analytic error (1st derivative): "<<max1<<" for x0="<<(double) index1/10<<"\n";
        cout<<"Maximum relative error (1st derivative): "<<max3<<" for x0="<<(double) index1/10<<"\n";
        cout<<"Maximum relative error (2nd derivative): "<<max4<<" for x0="<<(double) index2/10<<"\n";
        cout<<"Maximum analytic error (2nd derivative): "<<max2<<" for x0="<<(double) index2/10<<"\n";
}

int main()
{
    long double *coeff1;
    long double *coeff2;
    long double *val1_an, *val2_an, *val1_re, *val2_re;
    final_formula initial;


    int n=initial.getn1();
    coeff1= new long double[n];
    val1_an= new long double[11];
    val2_an= new long double[11];
    val1_re= new long double[11];
    val2_re= new long double[11];
    first_order(coeff1, initial.getn1());
    coeff2=second_order(coeff1, initial.getn1());
for(int i=0; i<11; i++)
    {
        cout<<"Values for: "<<(double) (i)/10<<"\n";
        initial.tab=initial.init_fullfill(initial.n1);
        initial.backward_diff(initial.n1);
        initial.ToVector(initial.n1);
        cout<<"First order derivative: "<<value_derivative_first(initial.tabvalues, coeff1, initial.h, initial.n1 )<<"\n";
        cout<<"Exact value: "<<derivative_first(initial.x0)<<"\n";
        val1_an[i]=abs(derivative_first(initial.x0)-value_derivative_first(initial.tabvalues, coeff1, initial.h, initial.n1 ));
        if(abs(derivative_first(initial.x0))!=0)
            val1_re[i]=abs(derivative_first(initial.x0)-value_derivative_first(initial.tabvalues, coeff1, initial.h, initial.n1 ))/abs(derivative_first(initial.x0));
        else
            val1_re[i]=abs(derivative_first(initial.x0)-value_derivative_first(initial.tabvalues, coeff1, initial.h, initial.n1 ))/(1+abs(derivative_first(initial.x0)));
        initial.tab=initial.init_fullfill(initial.n1+1);
        initial.backward_diff(initial.n1+1);
        initial.ToVector(initial.n1+1);
        cout<<"Second order derivative: "<<value_derivative_second(initial.tabvalues, coeff2, initial.h, initial.n1+1 )<<"\n";
        cout<<"Exact value: "<<derivative_second(initial.x0)<<"\n\n";
        val2_an[i]=abs(derivative_second(initial.x0)-value_derivative_second(initial.tabvalues, coeff2, initial.h, initial.n1+1 ));
        if(abs(derivative_second(initial.x0))!=0)
            val2_re[i]=abs(derivative_second(initial.x0)-value_derivative_second(initial.tabvalues, coeff2, initial.h, initial.n1+1 ))/abs(derivative_second(initial.x0));
        else
            val2_re[i]=abs(derivative_second(initial.x0)-value_derivative_second(initial.tabvalues, coeff2, initial.h, initial.n1+1 ))/(1+abs(derivative_second(initial.x0)));
        initial.x0+=0.1;
    }
    SearchMax(val1_an, val2_an, val1_re, val2_re, 11);
    system("pause");
    return 0;
}
