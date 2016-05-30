package MainPackage;

public class Integration_Calc {
	
	public static void main(String[] args) {
		
	double interval_a=1;
	double  interval_b=3;
	
	function funct= new function(interval_a, interval_b);
	double[] tab=new double[5];
	double[] taba=new double[6];
	double[] taba1=new double[6];
	double[] tab20= new double[6];
	double area1=0;
	double area2=0;
	double area3=0;
	double area4=0;
	double argmt=funct.interval_a;
	double argmt_prev=argmt;
	double small_interval;
	
	argmt=funct.interval_a;
	for(int i=0; i<5; i++)
	{
	tab[i]=funct.value(argmt);
	argmt+=(funct.interval_b-funct.interval_a)/4;
	}
	
	argmt=funct.interval_a;
	
	for(int i=0; i<6; i++)
	{
		//taba[i]=Integration_Calc.trapezoid_simple(funct.value(argmt), funct.value(argmt+(funct.interval_b-funct.interval_a)/6), (funct.interval_b-funct.interval_a)/6);
		taba1[i]=Integration_Calc.simpson_simple(funct.value(argmt), funct.value((argmt+argmt+(funct.interval_b-funct.interval_a)/6)/2), funct.value(argmt+(funct.interval_b-funct.interval_a)/6), (funct.interval_b-funct.interval_a)/6);
		argmt+=(funct.interval_b-funct.interval_a)/6;
		area3+=taba1[i];
	}
	argmt=funct.interval_a;
	for(int i=0; i<6; i++)
	{
		taba[i]=Integration_Calc.trapezoid_simple(funct.value(argmt), funct.value(argmt+(funct.interval_b-funct.interval_a)/6), (funct.interval_b-funct.interval_a)/6);
		//taba[i]=Integration_Calc.simpson_simple(funct.value(argmt), funct.value((argmt+argmt+(funct.interval_b-funct.interval_a)/6)/2), funct.value(argmt+(funct.interval_b-funct.interval_a)/6), (funct.interval_b-funct.interval_a)/6);
		argmt+=(funct.interval_b-funct.interval_a)/6;
		area4+=taba[i];
	}
	argmt=funct.interval_a;
		
	for(int i=0; i<6; i++)
	{
		
		tab20[i]=funct.value(argmt);
		area1=tab20[i]*(funct.interval_b-funct.interval_a)/5;
		argmt+=(funct.interval_b-funct.interval_a)/5;
		area2+=area1;
		
	}

	double[] tabcheb=new double[2];
	double[] tabcheb2=new double[2];
	double[] tabcheb4=new double[4];
	tabcheb4=Integration_Calc.x_cheb4(funct.interval_a, funct.interval_b);
	tabcheb2=Integration_Calc.x_cheb2(funct.interval_a, funct.interval_b);
	double result=0;
	double result1=0;
	double result2=0;
	result2=funct.value(funct.interval_a)*funct.interval_length();
	double result3=0;
	double result4=0;
	argmt=funct.interval_a;
	for(int i=0; i<5; i++)
		{result3+=funct.value(argmt)*(funct.interval_length()/5);
		argmt+=funct.interval_length()/5;
		}
	argmt=funct.interval_a;
	for(int i=0; i<100; i++)
	{result4+=funct.value(argmt)*(funct.interval_length()/100);
	argmt+=funct.interval_length()/100;
	}
	
	
	
	argmt=funct.interval_a;
for(int i=0; i<5; i++)
	{
	tabcheb=Integration_Calc.x_cheb2(argmt, (argmt+(funct.interval_b-funct.interval_a)/5));
	result+=Integration_Calc.cheb2_value((funct.interval_b-funct.interval_a)/5, funct.value(tabcheb[0]), funct.value(tabcheb[1]));
	argmt+=(funct.interval_b-funct.interval_a)/5;
	}

	result1=Integration_Calc.cheb2_value(funct.interval_length(), funct.value(tabcheb2[0]),funct.value(tabcheb2[1]));
	
	System.out.print("Interval: "+ funct.interval_length()+"\n");
	System.out.print("Rectangular(simple): "+result2+"\n");
	System.out.print("Rectangular(5 iteration): "+result3+"\n");
	System.out.print("Rectangular(5 iteration x 20): "+result4+"\n");
	System.out.print("Trapezoid(simple): "+ Integration_Calc.trapezoid_simple(funct.value(interval_b), funct.value(interval_a), funct.interval_length())+"\n");
	System.out.print("Simpson(simple): "+ Integration_Calc.simpson_simple(funct.value(interval_a),funct.value((interval_a+interval_b)/2), funct.value(interval_b), funct.interval_length())+"\n");
	System.out.print("n4(simple): "+Integration_Calc.n4(tab, funct.interval_length())+"\n");
	System.out.print("5 Intervals Simpson: "+area3+"\n");
	System.out.print("5 Intervals Trapezoid: "+area4+"\n");
	System.out.print("Chebyshev2 (5interval) "+ result+"\n");
	System.out.print("Chebyshev2 "+ result1+"\n");
	System.out.print("Chebyshev4(simple) "+ Integration_Calc.cheb4_value(funct.interval_length(), funct.value(tabcheb4[0]), funct.value(tabcheb4[1]), funct.value(tabcheb4[2]), funct.value(tabcheb4[3]) )+"\n");
	}
	static double trapezoid_simple(double val1, double val2, double interv)
	{
		return (interv/2)*(val1+ val2);
	}
	static double simpson_simple(double val1, double val2, double val3, double interv)
	{
		return (interv/6)*(val1+4*val2+val3);
	}
	static double n4(double[] tab, double interv)
	{
		double sum=7*(tab[0]+tab[4])+32*(tab[1]+tab[3])+12*tab[2];
		return (interv/90)*sum;
	}
	static double[] x_cheb2(double interval_a, double interval_b)
	{
		double tabx[]= new double[2];
		tabx[0]=0.5*(interval_a+interval_b)+0.5*(interval_a-interval_b)*(-0.57735);
		tabx[1]=0.5*(interval_a+interval_b)+0.5*(interval_a-interval_b)*0.57735;
		return tabx;
	}
	static double cheb2_value(double interval_length, double val1, double val2)
	{	double area=(interval_length/2)*(val1+val2);
		return area;
	}
	
	static double[] x_cheb4(double interval_a, double interval_b)
	{
		double tabx[]= new double[4];
		tabx[0]=0.5*(interval_a+interval_b)+0.5*(interval_a-interval_b)*(-0.7964654);
		tabx[1]=0.5*(interval_a+interval_b)+0.5*(interval_a-interval_b)*-0.187592;
		tabx[2]=0.5*(interval_a+interval_b)+0.5*(interval_a-interval_b)*0.187592;
		tabx[3]=0.5*(interval_a+interval_b)+0.5*(interval_a-interval_b)*0.794654;
		return tabx;
	}
	static double cheb4_value(double interval_length, double val1, double val2, double val3, double val4)
	{	double area=(interval_length/4)*(val1+val2+val3+val4);
		return area;
	}
}

