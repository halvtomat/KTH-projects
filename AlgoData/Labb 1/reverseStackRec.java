import java.util.Scanner;
/*  This class Recursively reverses a string
*/ 
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