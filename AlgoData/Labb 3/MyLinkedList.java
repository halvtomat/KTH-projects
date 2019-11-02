import java.util.Iterator;
import java.io.*;

public class MyLinkedList<Item> implements Iterable<Item>{
    private Node first;

    private class Node{
        Item item;
        Node next;
    }
    /*InsertFirst method inserts a new Node at the top of the queue and prints the whole queue*/
    public void insert(Item item){
        Node node = new Node();
        node.item = item;
        if(first == null){
            node.next = null;
            first = node;
        } else {
           node.next = first;
           first = node; 
        }
    }
    /*Print method prints the whole queue*/
    public String print(){
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

        public boolean hasNext() { return current.next != null;}
        public void remove() { /*not supported */}
        public Item next(){
            Item item = current.item;
            current = current.next;
            return item;
        }
    }
}