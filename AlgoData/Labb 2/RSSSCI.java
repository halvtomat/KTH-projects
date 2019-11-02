import java.util.Scanner;
public class RSSSCI{
    /*Sorts an array using the famous selection sort algorithm, but backwards*/
    public static int Sort(int[] a){
        int b = 0;
        for(int i = a.length-1; i >= 0; i--){
            int min = i;
            for(int j = i-1; j >= 0; j--){
                if(Less(a[j], a[min])) min = j;
            }
            if(min != i){
                Swap(a, i, min); 
                b++;
            } 
        }
        return b;
    }
    /*Returns a string with all inversions in an array
      Time complexity should be O(N*N) because the array is gone through once for every element, N*N times*/
    public static String Inversions(int[] a){
        String s = "";
        for(int i = a.length-1; i >= 0; i--){
            for(int j = i-1; j >= 0; j--){
                if(Less(a[j], a[i])) s = s+"( " + i + "," + a[i] + " : " + j + "," + a[j] + " )";
            }
        }
        return s;
    }
    /*Swaps two elements of an array*/
    private static void Swap(int[] a,int b,int c){
        int temp = a[b];
        a[b] = a[c];
        a[c] = temp;
    }
    /*Less method compares two ints and returns wheter the first one is smaller than the other*/
    private static boolean Less(int a, int b){
        return (a < b);
    }
    /*Print method prints the whole queue*/
    private static String Print(int[] a){
        String s = "";
        for(int i = 0; i < a.length; i++){
            s = s + a[i] + " ";
        }
        return s;
    }
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int N = scanner.nextInt();
        int[] a = new int[N];
        for(int i = 0; i < N; i++){
            a[i] = scanner.nextInt();
        }
        scanner.close();
        System.out.println("Unsorted Array: "+Print(a));
        System.out.println("Inversions: "+Inversions(a));
        int swaps = Sort(a);
        System.out.println("Sorted Array: "+Print(a)+"   Number of swaps: "+swaps);
    }
}