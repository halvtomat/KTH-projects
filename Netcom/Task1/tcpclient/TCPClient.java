package tcpclient;
import java.net.*;
import java.io.*;
import java.nio.charset.StandardCharsets;

public class TCPClient {

    private static int BUFFERSIZE = 1024;
    
    public static String askServer(String hostname, int port, String ToServer) throws  IOException {
        Socket clientSocket = new Socket(hostname, port);
        byte[] clientBuffer = ToServer.getBytes(StandardCharsets.UTF_8);
        byte[] serverBuffer = new byte[BUFFERSIZE];

        clientSocket.getOutputStream().write(clientBuffer, 0, clientBuffer.length);
        clientSocket.getOutputStream().write('\n');

        int lastIndex = 0;
        while(true){
            if(clientSocket.getInputStream().read(serverBuffer, lastIndex, serverBuffer.length-lastIndex) == serverBuffer.length-lastIndex){
                byte[] temp = serverBuffer;
                serverBuffer = new byte[2* temp.length];
                System.arraycopy(temp, 0, serverBuffer, 0, temp.length);
                lastIndex = temp.length;
            }
            else break;
        }

        String serverString = new String(serverBuffer, StandardCharsets.UTF_8);

        clientSocket.close();
        return serverString;
        
    }

    public static String askServer(String hostname, int port) throws  IOException {
        Socket clientSocket = new Socket(hostname, port);
        byte[] serverBuffer = new byte[BUFFERSIZE];

        clientSocket.getInputStream().read(serverBuffer);
        String serverString = new String(serverBuffer, StandardCharsets.UTF_8);

        clientSocket.close();
        return serverString;
    }
}