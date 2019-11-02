import java.io.*;

public class 2{

    public static void main(String[] args) throws IOException{
        FileReader fr;
        fr=new FileReader("/Users/Daniel/Documents/AlgoData/PrepLab/Assignment2/2input.txt");
        BufferedReader br = new BufferedReader(fr);
        int c;
        while((c = br.read()) != -1){
            if((char)c == 'a'){
                System.out.println('x');
            } else{
                System.out.println((char)c);
            }
        }
    }
}