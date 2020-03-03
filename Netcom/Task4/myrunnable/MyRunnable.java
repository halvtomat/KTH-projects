package myrunnable;
import java.nio.charset.StandardCharsets;
import java.net.*;
import java.io.*;
import tcpclient.TCPClient;

public class MyRunnable implements Runnable {

    private Socket client;
    private int req_port;
    private String req_hostname;
    private String req_string;

    public MyRunnable (Socket client){
        this.client = client;
        this.req_port = 0;
        this.req_hostname = "";
        this.req_string = "";
    }

    public void run() throws RuntimeException{

        try {
            String req = get_response(client);
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
            try {
                if(req_hostname.equals("") | req_port == 0 | !req_split[0].equals("GET") | !req_split[1].equals("/ask")){
                    byte[] header = "HTTP/1.1 400 BAD REQUEST\r\n\r\n".getBytes(StandardCharsets.UTF_8);
                    client.getOutputStream().write(header);
                    client.close();
                    return;
                }
            } catch (ArrayIndexOutOfBoundsException e) {
                byte[] header = "HTTP/1.1 400 BAD REQUEST\r\n\r\n".getBytes(StandardCharsets.UTF_8);
                client.getOutputStream().write(header);
                client.close();
                return;
            }

            String serverOutput = "";
            try {
                if(req_string.equals("")) serverOutput = TCPClient.askServer(req_hostname, req_port);
                else serverOutput = TCPClient.askServer(req_hostname, req_port, req_string);
                
            //Handle HTTP 404
            } catch (UnknownHostException e) {
                byte[] header = "HTTP/1.1 404 NOT FOUND\r\n\r\n".getBytes(StandardCharsets.UTF_8);
                client.getOutputStream().write(header);
                client.close();
                return;
            }

            byte[] header = "HTTP/1.1 200 OK\r\n\r\n".getBytes(StandardCharsets.UTF_8);
            client.getOutputStream().write(header);
            client.getOutputStream().write(serverOutput.getBytes(StandardCharsets.UTF_8));
            client.close();
            return;

        } catch (IOException e) {
            throw new RuntimeException();
        }

    }


    private static String get_response(Socket clientSocket) throws IOException {
        byte[] serverBuffer = new byte[1024];
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
        return serverString.trim();
    }
}