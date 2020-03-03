import java.net.*;
import java.io.*;
import myrunnable.MyRunnable;

public class ConchHTTPAsk {
    public static void main( String[] args) throws IOException{
        int port = Integer.parseInt(args[0]);
        ServerSocket serverSocket = new ServerSocket(port);

        while(true){
            Socket connected = serverSocket.accept();            
            Thread t = new Thread(new MyRunnable(connected));
            t.start();
        }
    }

}

