import java.io.*;
import java.util.*;

public class 3{
    public static void main(String[] args)throws IOException{
        int nrElements;
        FileReader fr = new FileReader("/Users/Daniel/Documents/AlgoData/PrepLab/Assignment3/3input.txt");
        Scanner scan = new Scanner(fr);
        nrElements = scan.nextInt();

        int[] intArray = new int[nrElements];
        
        for (int i = 0; i < intArray.length; i++){
            nrElements = scan.nextInt();
            intArray[i] = nrElements;
        }
        fr.close();

        for(int i = 0; i < intArray.length; i++){
            System.out.println(intArray[intArray.length - (i+1)]);
        }
    }
}