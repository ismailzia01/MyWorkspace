import java.util.Scanner;

public class PrintNum {
    public static void main(String[] args) {
        int num1 = 1;
        int num2 = 2;
        Scanner input = new Scanner(System.in);
        System.out.print("Enter no. of terms to be printed : ");
        int num = input.nextInt();
        while (num > 0) {
            int result = (num2*num2) - (num1*num1);
            System.out.print(result + " " );
            num1 = num2;
            num2 += 1;
            num--;
        }
        input.close();
    }
}
