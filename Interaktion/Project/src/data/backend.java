import java.net.*;
import java.io.*;
import java.nio.charset.StandardCharsets;

public class backend {

    public static void getCurrentWeather() throws IOException{
        URL url = new URL("http://api.openweathermap.org/data/2.5/weather?q=London,uk&appid=50681dec8da1106ac97805a58d14eec5");
        HttpURLConnection con = (HttpURLConnection) url.openConnection();
        con.setRequestMethod("GET");
        con.setRequestProperty("Content-Type", "application/json");

        BufferedReader in = new BufferedReader(new InputStreamReader(con.getInputStream()));
        String inputLine;
        StringBuffer content = new StringBuffer();
        while((inputLine = in.readLine()) != null){
            content.append(inputLine);
        }
        in.close();

        System.out.println(con.getResponseCode() + " " + con.getResponseMessage());
        System.out.println(content);
    }
    public static void main(String[] args) throws IOException{
        getCurrentWeather();
    }
}

