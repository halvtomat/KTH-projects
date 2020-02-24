import java.net.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import tcpclient.TCPClient;

public class HTTPAsk {
    public static void main( String[] args) throws IOException{
        int port = Integer.parseInt(args[0]);
        ServerSocket serverSocket = new ServerSocket(port);

        while(true){
            Socket connected = serverSocket.accept();

            byte[] header = "HTTP/1.1 200 OK\r\n\r\n".getBytes(StandardCharsets.UTF_8);
            connected.getOutputStream().write(header);
            byte[] client_req = new byte[2048];
            connected.getInputStream().read(client_req);
            String req = new String(client_req, StandardCharsets.UTF_8);
            System.out.print(req);
            String[] req_split = req.split("\n");
            System.out.println(req_split[1]);
            String[] req_split_split = req_split[1].split(":");
            System.out.println(req_split_split[1]);
            System.out.println(req_split_split[2]);
            String req_hostname = req_split_split[1];
            int req_port = Integer.parseInt(req_split_split[2]);
            String ServerOutput = TCPClient.askServer(req_hostname, req_port);
            System.out.println(ServerOutput);
        }
    }
}

