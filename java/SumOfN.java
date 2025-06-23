//Sum of first n number using recursion 
import java.util.Scanner;
public class SumOfN {
    public static int sumOfN(int n) {
        if(n < 1)
            return 0;
        return n + sumOfN(n-1);
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        System.out.print("Enter value of N : ");
        int n = input.nextInt();
        System.out.println("Sum of first N numbers : " + sumOfN(n));
        input.close();
    }
}
