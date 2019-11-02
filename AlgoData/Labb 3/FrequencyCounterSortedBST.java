import java.util.Scanner;
public class FrequencyCounterSortedBST{
    public static void main(String[] args)throws Exception {
        int minLen = Integer.parseInt(args[0]);
        BST<String,Integer> st = new BST<String,Integer>();
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
        String[] sa = new String[Integer.parseInt(args[1])*100];
        int i = 0;
        for(String word : st.keys()){
            if(st.get(word) > st.get(max))max = word;
            sa[i++] = word;
        }
        Sort(sa,st);
        i--;
        int n = i;
        for(i-=(Integer.parseInt(args[2]));i > n-(Integer.parseInt(args[3]));i--){
            System.out.println(sa[i]+" "+st.get(sa[i]));  
        }
        
    }
    private static void Sort(String[] a,BST<String,Integer> st){
        for(int i = 0; i < a.length; i++){
            if(a[i] == null) break;
            int min = i;
            for(int j = i+1; j < a.length; j++){
                if(a[j] == null) break;
                if(Less(st.get(a[j]), st.get(a[min]))) min = j;
            }
            if(min != i) Swap(a, i, min);
        }
    }
    /*Swaps two elements of an array*/
    private static void Swap(String[] a,int b,int c){
        String temp = a[b];
        a[b] = a[c];
        a[c] = temp;
    }
    /*Less method compares two ints and returns wheter the first one is smaller than the other*/
    private static boolean Less(int a, int b){
        return (a < b);
    }
}