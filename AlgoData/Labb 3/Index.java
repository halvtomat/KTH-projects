import java.util.*;
import java.io.*;

public class Index{
    public static void main(String[] args) throws Exception {
        Scanner scanner = new Scanner(System.in);
        String[] arr = new String[1000000];
        int i = 0;
        while(System.in.read() != -1){
            arr[i++] = scanner.next();
        }
        scanner.close();
        String findThis = args[0];
        System.out.println(findThis+ " Found at indices: ");
        for(i = 0; i < arr.length;i++){
            if(findThis.equals(arr[i])) System.out.println(i);
        }
    }
}