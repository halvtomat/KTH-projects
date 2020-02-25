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
            String req_hostname = "";
            int req_port = 0;
            String req_string = "";

            byte[] client_req = new byte[2048];
            connected.getInputStream().read(client_req);
            String req = new String(client_req, StandardCharsets.UTF_8);
            String[] req_split = req.split("[:?&= ]");

            for(int i = 0; i < req_split.length; i++){
                if(req_split[i].equals("Host")){
                    req_hostname = req_split[i+1];
                    req_port = Integer.parseInt(req_split[i+2]);
                    break;
                }
                if(req_split[i].equals("hostname")){
                    req_hostname = req_split[i+1];
                    continue;
                }
                if(req_split[i].equals("port")){
                    req_port = Integer.parseInt(req_split[i+1]);
                    continue;
                }
                if(req_split[i].equals("string")){
                    req_string = req_split[i+1];
                    continue;
                }
            }

            //Handle HTTP 400 
            if(req_hostname.equals("") | req_port == 0 | !req_split[0].equals("GET") | !req_split[1].equals("/ask")){
                byte[] header = "HTTP/1.1 400 BAD REQUEST\r\n\r\n".getBytes(StandardCharsets.UTF_8);
                connected.getOutputStream().write(header);
                connected.close();
                continue;
            }

            String serverOutput = "";
            try {
                if(req_string.equals("")) serverOutput = TCPClient.askServer(req_hostname, req_port);
                else serverOutput = TCPClient.askServer(req_hostname, req_port, req_string);
                
            //Handle HTTP 404
            } catch (UnknownHostException e) {
                byte[] header = "HTTP/1.1 404 NOT FOUND\r\n\r\n".getBytes(StandardCharsets.UTF_8);
                connected.getOutputStream().write(header);
                connected.close();
                continue;
            }

            byte[] header = "HTTP/1.1 200 OK\r\n\r\n".getBytes(StandardCharsets.UTF_8);
            connected.getOutputStream().write(header);
            connected.getOutputStream().write(serverOutput.getBytes(StandardCharsets.UTF_8));
            connected.close();
        }
    }
}

