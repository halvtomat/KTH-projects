import java.util.Scanner;
/*  This file is dependent on the CharStack java class */
public class BracketFilter {
    public static boolean isBalanced(String s){
        CharStack cs = new CharStack();
        int i = 0;
        char c;
        while(i < s.length()){
            c = s.charAt(i++);
            if(c == '(' || c == '{' || c == '[' ){
                cs.Push(c);
            }else if(cs.isEmpty() == false){
                if(c == ')'){
                    if(cs.Peek() == '(') cs.Pop();
                }else if(c == '}'){
                    if(cs.Peek() == '{') cs.Pop();
                }else if(c== ']'){
                    if(cs.Peek() == '[') cs.Pop();
                }
            }else if(cs.isEmpty() && (c == ')' || c == '}' || c == ']')){
                cs.Push('X');
                break;
            }
        }
        return cs.isEmpty();
    }
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String s = scanner.nextLine();
        scanner.close();

        if(isBalanced(s)) System.out.println("The string is balanced!");
        else System.out.println("The string is not balanced");

        assert (isBalanced("()"));
        assert !(isBalanced("("));
        assert !(isBalanced("[{]}"));
        assert (isBalanced("{(1+1)*a[32]}"));
        assert (isBalanced("f[asdf{asdfsdfasdf(dafadf)gfdasadf}d,.gm,.a]sfdsg41s234dfdafsasdf(adsf(adf)dadsf)s"));
    }
}