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
            String[] req_split = req.split(":");
            String req_hostname = req_split[1].trim();
            int req_port = Integer.parseInt(req_split[2].split("\n")[0].trim());
            String serverOutput = TCPClient.askServer(req_hostname, req_port);
            System.out.println(serverOutput);
            connected.getOutputStream().write(serverOutput.getBytes(StandardCharsets.UTF_8));
        }
    }
}

