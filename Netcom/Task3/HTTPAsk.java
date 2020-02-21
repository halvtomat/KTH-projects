import java.net.*;
import java.io.*;
import tcpclient.TCPClient;

public class HTTPAsk {
    public static void main( String[] args) {
        int port = Integer.parseInt(args[0]);
        ServerSocket serverSocket = new ServerSocket(port);

        while(true){
            Socket connected = serverSocket.accept();

            byte[] header = "HTTP/1.1 200 OK\r\n\r\n".getBytes(StandardCharsets.UTF_8);
            connected.getOutputStream().write(header);
        }
    }
}

