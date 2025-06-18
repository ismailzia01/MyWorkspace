import java.util.Scanner;

public class StackLL {
    class Node {
        int data;
        Node next;

        Node(int val) {
            data = val;
            next = null;
        }
    }

    private Node top = null;
    private Scanner input = new Scanner(System.in);

    public void pushItem() {
        System.out.print("Enter item: ");
        int ele = input.nextInt();
        Node new_node = new Node(ele);
        new_node.next = top;
        top = new_node;
    }

    public void popItem() {
        if (top == null) {
            System.out.println("Stack is Empty!");
            return;
        }
        System.out.println("Popped item: " + top.data);
        top = top.next;
    }

    public void peekItem() {
        if (top == null) {
            System.out.println("Stack is Empty!");
            return;
        }
        System.out.println("Peek item: " + top.data);
    }

    public void display() {
        if (top == null) {
            System.out.println("Stack is Empty!");
            return;
        }
        Node temp = top;
        System.out.println("Stack elements:");
        while (temp != null) {
            System.out.println(temp.data);
            temp = temp.next;
        }
    }

    public void run() {
        int choice;
        do {
            System.out.println("\n1) Push");
            System.out.println("2) Pop");
            System.out.println("3) Peek");
            System.out.println("4) Display");
            System.out.println("5) Exit");
            System.out.print("Enter Your Choice: ");
            choice = input.nextInt();

            switch (choice) {
                case 1 -> pushItem();
                case 2 -> popItem();
                case 3 -> peekItem();
                case 4 -> display();
                case 5 -> System.out.println("Exiting...");
                default -> System.out.println("Invalid Input!");
            }
        } while (choice != 5);

        input.close();
    }

    public static void main(String[] args) {
        StackLL stack = new StackLL();
        stack.run();
    }
}

