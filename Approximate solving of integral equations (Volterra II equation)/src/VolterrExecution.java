import java.awt.List;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.Writer;
import java.util.LinkedList;
import java.util.Scanner;

public class VolterrExecution {

	int p, iterations, size;
	double a, b, h;

	double[][] y;
	double[] x;

	double k(double arg) { // k(z)
		return (Math.sin(arg));
	}

	double f(double arg) { // f(x)
		return (Math.cos(arg));
	}

	void SetInterval() {
		Scanner sc = new Scanner(System.in);
		System.out.println("Left bound of integral's interval");
		this.a = sc.nextInt();
		System.out.println("Right bound of integral's interval");
		this.b = sc.nextInt();
		System.out.println("Parameter");
		this.p = sc.nextInt();
		System.out.println("Number of iterations");
		this.iterations = sc.nextInt();
		System.out.println("Step");
		this.h = sc.nextDouble();
	}

	void InitialSet() {
		size = (int) ((b - a) / h);
		this.y = new double[size + 1][iterations + 1];
		this.x = new double[size+1];
		x[0] = a;
	}

	void FillArguments() {

		for (int i = 1; i <= size; i++) {
			x[i] = x[i - 1] + h;
		}
	}

	void FileWriting() {
		BufferedWriter writer_x = null;
		BufferedWriter writer_y = null;
		try {
			File file_x = new File("Input(x).txt");
			File file_y = new File("Output(y).txt");
			writer_x = new BufferedWriter(new FileWriter(file_x));
			writer_y = new BufferedWriter(new FileWriter(file_y));
			
			for (int i = 0; i <= size; i++) {
				writer_x.write(String.valueOf(x[i]));
				writer_x.newLine();
			}
			
			for(int i=1; i<=iterations; i++){
				writer_y.write("Iteration ");
				writer_y.write(String.valueOf(i));
				writer_y.newLine();
				for(int j=1; j<size; j++){
					writer_y.write(String.valueOf(y[j][i]));
					writer_y.newLine();
				}
			}

		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (writer_x != null) {
				try {
					writer_x.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
			if (writer_y != null) {
				try {
					writer_y.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}
	}

	void VolterraPerform() {

		for (int k = 0; k < iterations; k++) {
			System.out.println("Iteration " + (k + 1));
			for (int j = 1; j < size; j++) {
				for (int i = 1; i < j; i++) {
					y[j][k + 1] = k(x[j] - x[i]) * y[i][k] * h + y[j][k + 1];
				}
				y[j][k + 1] = p * y[j][k + 1] + f(x[j]);
				System.out.print(y[j][k + 1] + "; ");

			}
			System.out.println("");
		}

	}

	public VolterrExecution() {

		SetInterval();
		InitialSet();
		FillArguments();
		VolterraPerform();
		FileWriting();
	}

}
