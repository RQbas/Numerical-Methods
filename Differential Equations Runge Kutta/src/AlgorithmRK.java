import java.io.IOException;
import java.util.InputMismatchException;
import java.util.Scanner;

public class AlgorithmRK {

	

	double x_init;
	double y_init;
	double H;
	int iteration;
	
	
	void User_Input(){
		System.out.println("Enter Initial y");
		Scanner sc=new Scanner(System.in);
		try{
			this.y_init=sc.nextDouble();
			System.out.println("Enter Initial x");
			this.x_init=sc.nextDouble();
			System.out.println("Enter step");
			this.H=sc.nextDouble();
			System.out.println("Enter iterations");
			this.iteration=sc.nextInt();
		}catch(InputMismatchException e)
			{
				System.out.println("Wrong input");
			}
		sc.close();
	}
	void show(double a){
		System.out.printf("%-25s", a);
	}
	void title(String a){
		System.out.printf("%-25s", a);
	}
	void n(){
		System.out.println("");
	}
	
double f(double x, double y){
		return y*Math.tan(x)+1/(Math.cos(x));
	}
	void alg(){
		double k1=0, k2=0, k3=0, k4=0, deltay = 0;
		for(int i=0; i<iteration; i++){
			System.out.println("i="+i);
			title("x");
			title("y");
			title("k=h*f");
			title("delta y");
			n();
			for(int j=0; j<4; j++){
				switch(j){
				case 0:{
					show(x_init);
					show(y_init);
					k1=H*f(x_init, y_init);
					show(k1);
					deltay=k4;;
					show(deltay);
					n();
					break;
				}
				case 1:{
					show(x_init+H/2);
					show(y_init+k1/2);
					k2= H*f(x_init+H/2, y_init+k1*H/2);
					show(k2);
					deltay=2*k2;
					show(deltay);
					n();
					break;
					
				}
				case 2:{
					show(x_init+H/2);
					show(y_init+k2/2);
					k3= H*f(x_init+H/2, y_init+k2*H/2);
					show(k3);
					deltay=2*k3;
					show(deltay);
					n();
					break;
				}
				case 3:{
					show(x_init+H);
					show(y_init+k3);
					k4 = H*f(x_init+H, y_init+k3*H);
					show(k4);
					deltay=(k4);
					show(deltay);
					n();
					x_init+=H;
					break;
				}
				}
				
			}
			deltay=(k1+2*k2+2*k3+k4)/6;
			System.out.print("delta y"+i+":   ");
			show(deltay);
			n();
			y_init+=deltay;
			n();
			n();
		
		}
	}
	public AlgorithmRK() {
		User_Input();
		alg();
	}

}
