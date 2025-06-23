import java.util.ArrayList;
import java.util.Scanner;

public class DynamicInput {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        ArrayList<Integer> numbers = new ArrayList<>();

        System.out.println("Enter numbers (type any non-integer to stop):");

        while (sc.hasNextInt()) {
            int num = sc.nextInt();
            numbers.add(num);
        }

        System.out.println("\nYou entered " + numbers.size() + " numbers:");
        for (int n : numbers) {
            System.out.print(n + " ");
        }
        System.out.println();
    }
}

