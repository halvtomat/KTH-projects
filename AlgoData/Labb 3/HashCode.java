import java.util.*;

public class HashCode {
    public static void main(String[] args)throws Exception {
        int collisions = 0;
        int uniqeWords = 0;
        MyLinkedList<String> words = new MyLinkedList<String>();
        MyLinkedList<Integer> hashes = new MyLinkedList<Integer>();
        Scanner scanner = new Scanner(System.in);
        for(int i = 0; i < Integer.parseInt(args[0])*100; i++){
            if(System.in.read() == -1) break;
            String word = scanner.next();
            if(!words.contains(word)){
                uniqeWords++;
                words.insert(word);
                if(hashes.contains(word.hashCode())) collisions++;
                else hashes.insert(word.hashCode());
            }
        }
        scanner.close();
        System.out.println("Unique words: " + uniqeWords);
        System.out.println("Collisions: " + collisions);
        System.out.println("Collisionrate: " + (float)(collisions/uniqeWords)*100 + "%");
    }
}
