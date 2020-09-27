import java.util.Scanner;
import java.time.Clock;
public class FrequencyCounterOAST{
    public static void main(String[] args)throws Exception {
        int minLen = Integer.parseInt(args[0]);
        OrderedArrayST<String,Integer> st = new OrderedArrayST<String,Integer>(Integer.parseInt(args[1]) * 100);
        Scanner scanner = new Scanner(System.in);
        Clock clock = Clock.systemDefaultZone();
        long s,t;
        s = clock.millis();
        for(int i = 0; i < Integer.parseInt(args[1])*100;i++){
            if(System.in.read() == -1) break;
            String word = scanner.next();
            if(word.length() < minLen) continue;
            if(st.get(word) == null) st.put(word,1);
            else st.put(word,st.get(word)+1);
        }
        t = clock.millis()-s;
        scanner.close();
        String max = "";
        s = clock.millis();
        st.put(max,0);
        for(String word : st.keys()){
            if(st.get(word) > st.get(max)) max = word;
        }
        t = t + (clock.millis()-s);
        System.out.println("Time Taken: " + t+" ms");
    }
}
