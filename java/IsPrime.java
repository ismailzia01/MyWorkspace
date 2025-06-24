import java.util.Scanner;

public class IsPrime {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int flag = 1;
        System.out.print("Enter a num : ");
        int num = input.nextInt();
        for(int i = 2; i < num/2; i++) {
            if(num % i == 0) {
                flag = 0;
                break;
            }
        }
        System.out.println((flag==1)?"Prime":"Not Prime");
        input.close();
    }
}
