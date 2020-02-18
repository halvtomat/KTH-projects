import java.net.*;
import java.nio.charset.StandardCharsets;
import java.io.*;

public class HTTPEcho {
    public static void main( String[] args) throws IOException {
        int port = Integer.parseInt(args[0]);
        ServerSocket serverSocket = new ServerSocket(port);

        while(true){
            Socket connectedSocket = serverSocket.accept();

            byte[] echo = get_input(connectedSocket);
            byte[] header = "HTTP/1.1 200 OK\r\n\r\n".getBytes(StandardCharsets.UTF_8);

            connectedSocket.getOutputStream().write(header);
            connectedSocket.getOutputStream().write(echo);
            connectedSocket.close();
        }
        
    }
    private static byte[] get_input(Socket connectedSocket) throws IOException {
        byte[] echoBuffer = new byte[1024];
        int lastIndex = 0;
        while(true){
            if(connectedSocket.getInputStream().read(echoBuffer, lastIndex, echoBuffer.length-lastIndex) == echoBuffer.length-lastIndex){
                byte[] temp = echoBuffer;
                echoBuffer = new byte[2* temp.length];
                System.arraycopy(temp, 0, echoBuffer, 0, temp.length);
                lastIndex = temp.length;
            }
            else break;
        }
        return echoBuffer;
    }
}

