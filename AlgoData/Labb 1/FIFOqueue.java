import java.util.Iterator;
import java.util.ListIterator;
import java.io.*;

public class FIFOqueue<Item> implements Iterable<Item>{
    private Node head;

    private class Node{
        Item item;
        Node next;
        Node prev;
    }
    /*Insert method inserts a new Node at the top of the queue*/
    public void Insert(Item item){
        Node node = new Node();
        node.item = item;
        if(head == null){
            node.next = node;
            node.prev = node;
            head = node;
        } else if(head.next == head){
            head.next = node;
            head.prev = node;
            node.next = head;
            node.prev = head;
            head = node;
        } else {
           node.prev = head.prev;
           node.next = head;
           head.prev.next = node;
           head.prev = node;
           head = node; 
        }
    }
    /*Delete method deletes the last Node in the queue and returns the item of the last Node*/
    public Item Delete(){
        Node n = head.prev;
        if(n == head){
            head = null;
        }
        else{
        n.next.prev = n.prev;
        n.prev.next = n.next;
        head = n.next;
        }
        return n.item;
    }
    /*Print method prints the whole queue*/
    public String Print(){
        String out = "";
        if(head == null){
            return out;
        }
        Node n = head;
        out = n.item + " ";
        while(n.next != head){
            n = n.next;
            out = out + n.item + " ";
        }

        return out+"\n";
    }
    /*Iterator implementation copied from book*/
    public Iterator<Item> iterator(){ return new ListIterator();}

    private class ListIterator implements Iterator<Item>{
        private Node current = head;

        public boolean hasNext() { return current != null;}
        public void remove() { /*not supported */}
        public Item next(){
            Item item = current.item;
            current = current.next;
            return item;
        }
    }

    public static void main(String[] args) {
        FIFOqueue<Integer> q = new FIFOqueue<Integer>();

        q.Insert(1);
        q.Insert(5);
        q.Insert(993);
        q.Insert(756);
        q.Insert(53);
        q.Insert(79542);
        assert (1 == q.Delete());
        assert (5 == q.Delete());
        Iterator<Integer> i = q.iterator();
        assert i.hasNext();
        assert (79542 == i.next());
        assert (53 == i.next());
        assert (756 == i.next());
        assert (993 == i.next());
        assert (993 == q.Delete());
        assert (756 == q.Delete());
        assert (53 == q.Delete());
        assert (79542 == q.Delete());
        i = q.iterator();
        assert !i.hasNext();
        q = null;
        i = null;
    }
}