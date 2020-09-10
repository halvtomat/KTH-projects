import java.util.Scanner;
/*  This class implements a CharStack to reverse a string of characters.
    Scan the next line into a string, go through all the characters in the string and add them to the CharStack.
    Last step is to Pop all the characters back and print them in reverse order.*/ 
public class reverseStackRec{
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String s = scanner.next();
        scanner.close();
        recur(s,0);
    }

    private static void recur(String s, int i){
        if(i == s.length()) return;
        recur(s, i+1);
        System.out.print(s.charAt(i));
    }
}