import java.util.*;

public class OrderedArrayST<Key extends Comparable<Key>, Value>{
    private Key[] keys;
    private Value[] vals;
    private int n = 0;

    public OrderedArrayST(int capacity){
        keys = (Key[]) new Comparable[capacity];
        vals = (Value[]) new Object[capacity];
    }
    public int rank(Key key) {
        if (key == null) throw new IllegalArgumentException("argument to rank() is null"); 

        int lo = 0, hi = n-1; 
        while (lo <= hi) { 
            int mid = lo + (hi - lo) / 2; 
            int cmp = key.compareTo(keys[mid]);
            if      (cmp < 0) hi = mid - 1; 
            else if (cmp > 0) lo = mid + 1; 
            else return mid; 
        } 
        return lo;
    } 
    public void put(Key key, Value val)  {
        if (key == null) throw new IllegalArgumentException("first argument to put() is null"); 
        int i = rank(key);

        // key is already in table
        if (i < n && keys[i].compareTo(key) == 0) {
            vals[i] = val;
            return;
        }

        for (int j = n; j > i; j--)  {
            keys[j] = keys[j-1];
            vals[j] = vals[j-1];
        }
        keys[i] = key;
        vals[i] = val;
        n++;
    } 
    public int size() {
        return n;
    }
    public boolean isEmpty() {
        return size() == 0;
    }
    public Value get(Key key) {
        if (key == null) throw new IllegalArgumentException("argument to get() is null"); 
        if (isEmpty()) return null;
        int i = rank(key); 
        if (i < n && keys[i].compareTo(key) == 0) return vals[i];
        return null;
    } 
    public boolean contains(Key key) {
        if (key == null) throw new IllegalArgumentException("argument to contains() is null");
        return get(key) != null;
    }
    public Key min() {
        if (isEmpty()) return null;
        return keys[0]; 
    }
    public Key max() {
        if (isEmpty()) return null;
        return keys[n-1];
    }
    public Iterable<Key> keys() {
        Key hi = max();
        Key lo = min();
        MyLinkedList<Key> queue = new MyLinkedList<Key>(); 
        if (lo.compareTo(hi) > 0) return queue;
        for (int i = rank(lo); i < rank(hi); i++) 
            queue.insert(keys[i]);
        if (contains(hi)) queue.insert(keys[rank(hi)]);
        return queue; 
    }
    public static void main(String[] args) {
        OrderedArrayST<String,Integer> st = new OrderedArrayST<String,Integer>(10);
        st.put("a",4);
        st.put("agas",7);
        st.put("g",40);
        st.put("dfadf",1);
        st.put("hhjdgf",23130);

        for(String word : st.keys()){
            System.out.print(word + " " + st.get(word)+ "\n");
        }
    }
}

