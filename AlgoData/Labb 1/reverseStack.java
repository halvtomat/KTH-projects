import java.util.Scanner;
/*  This class implements a CharStack to reverse a string of characters.
    Scan the next line into a string, go through all the characters in the string and add them to the CharStack.
    Last step is to Pop all the characters back and print them in reverse order.*/ 
public class reverseStack{
    public static void main(String[] args) {
        CharStack stack = new CharStack();
        Scanner scanner = new Scanner(System.in);
        String s = scanner.nextLine();
        scanner.close();
        for(int i = 0; i < s.length();i++){
            stack.Push(s.charAt(i));
        }
        for(int i = 0; i < s.length();i++){
            System.out.print(stack.Pop());
        }
    }
}