import java.util.Scanner;

public class FrequencyCounterOAST{
    public static void main(String[] args)throws Exception {
        int minLen = Integer.parseInt(args[0]);
        OrderedArrayST<String,Integer> st = new OrderedArrayST<String,Integer>(Integer.parseInt(args[1]) * 100);
        Scanner scanner = new Scanner(System.in);
        for(int i = 0; i < Integer.parseInt(args[1])*100;i++){
            if(System.in.read() == -1) break;
            String word = scanner.next();
            if(word.length() < minLen) continue;
            if(st.get(word) == null) st.put(word,1);
            else st.put(word,st.get(word)+1);
        }
        scanner.close();
        String max = "";
        st.put(max,0);
        for(String word : st.keys()){
            if(st.get(word) > st.get(max)) max = word;
        }
        System.out.println(max +" "+st.get(max));
    }
}
