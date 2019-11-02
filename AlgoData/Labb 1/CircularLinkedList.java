import java.util.Iterator;
import java.io.*;

public class CircularLinkedList<Item> implements Iterable<Item>{
    private Node first;
    private Node last;

    private class Node{
        Item item;
        Node next;
    }
    /*InsertFirst method inserts a new Node at the top of the queue and prints the whole queue*/
    public void InsertFirst(Item item){
        Node node = new Node();
        node.item = item;
        if(first == null){
            node.next = node;
            first = node;
            last = node;
        } else if(first.next == first){
            first.next = node;
            node.next = first;
            last = first;
            first = node;
        } else {
           node.next = first;
           last.next = node;
           first = node; 
        }
        System.out.print(Print());
    }
        /*InsertLast method inserts a new Node at the bottom of the queue and prints the whole queue*/
        public void InsertLast(Item item){
            Node node = new Node();
            node.item = item;
            if(last == null){
                node.next = node;
                first = node;
                last = node;
            } else if(last.next == last){
                last.next = node;
                node.next = first;
                first = last;
                last = node;

            } else {
               node.next = first;
               last.next = node;
               last = node; 
            }
            System.out.print(Print());
        }
    /*RemoveFirst method removes the first Node in the queue and returns the item of the first Node, also prints the whole queue*/
    public Item RemoveFirst(){
        Node n = first;
        if(first == last){
            first = null;
            last = null;
        }else{
            first = n.next;
            last.next = first;
        }
        n.next = null;
        System.out.print(Print());
        return n.item;
    }
    /*RemoveLast method removes the last Node in the queue and returns the item of the last Node, also prints the whole queue*/
    public Item RemoveLast(){
        Node n = last;
        if(first == last){
            last = null;
            first = null;
        }else{
            last = findPrevToLast(n);
            last.next = first;
        }
        n.next = null;
        System.out.print(Print());
        return n.item;
    }
    /* Recursive method to find the Node that points to the last Node, AKA the Node previous to the last Node*/
    private Node findPrevToLast(Node n){
        if(n.next != last) n = findPrevToLast(n.next);
        return n;
    }
    /*Print method prints the whole queue*/
    public String Print(){
        String out = "";
        if(first == null){
            return out;
        }
        Node n = first;
        out = n.item + " ";
        while(n.next != first){
            n = n.next;
            out = out + n.item + " ";
        }

        return out+"\n";
    }
    /*Iterator implementation copied from book*/
    public Iterator<Item> iterator(){ return new ListIterator();}

    private class ListIterator implements Iterator<Item>{
        private Node current = first;

        public boolean hasNext() { return current != null;}
        public void remove() { /*not supported */}
        public Item next(){
            Item item = current.item;
            current = current.next;
            return item;
        }
    }

    public static void main(String[] args) {
        CircularLinkedList<Integer> q = new CircularLinkedList<Integer>();
        Iterator<Integer> i = q.iterator();

        assert !i.hasNext();
        q.InsertFirst(1);
        q.InsertFirst(5);
        q.InsertFirst(993);
        q.InsertLast(756);
        q.InsertLast(53);
        q.InsertLast(79542);
        assert (79542 == q.RemoveLast());
        assert (993 == q.RemoveFirst());
        i = q.iterator();
        assert i.hasNext();
        assert (5 == i.next());
        assert (1 == i.next());
        assert (756 == i.next());
        assert (53 == i.next());
        assert (53 == q.RemoveLast());
        assert (5 == q.RemoveFirst());
        assert (756 == q.RemoveLast());
        assert (1 == q.RemoveFirst());
        i = q.iterator();
        assert !i.hasNext();
        q = null;
        i = null;
    }
}