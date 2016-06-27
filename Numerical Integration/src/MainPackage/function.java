package MainPackage;
import java.lang.Math;

public class function {

	double interval_a;
	double interval_b;
	
	public function(double a, double b)
	{
		interval_a=a;
		interval_b=b;
	}
	
	double interval_length()
	{
		double h=(interval_b-interval_a);
		return h;
	}
	double value(double arg)
		{
		double funct_val=2*arg*(-1*Math.cos(Math.pow(arg, 2)))*Math.exp(-1*Math.sin(Math.pow(arg,  2)));
				
		return funct_val;
		
		}
	}


